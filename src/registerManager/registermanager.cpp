#include "src/registerManager/registermanager.h"
#include "src/HeaderManager/headermanager.h"
#include "src/dataStructures/SimpleList.h"
#include "src/Register/register.h"
#include "src/stringProcessor/decript.h"
#include "readfile.h"
#include "writefile.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "simpletoarr.h"

using namespace std;

RegisterManager::RegisterManager (string tableName,
                                  SimpleList< char* >* tableColumns,
                                  SimpleList<int>* columnsize, int regSize) {
    //table creation
    Header = new HeaderManager(regSize);
    Reg = new Register(tableColumns, columnsize);
    filesystem = new FSQLServerFileSystem();
    createHardTable(tableName, tableColumns, columnsize, regSize);

}

void RegisterManager::createHardTable(string tableName,
                                      SimpleList<char *>* tableColumns,
                                      SimpleList<int>* columnsize,
                                      int regSize) {

    simpleToArr<char*>* ARR1 = new simpleToArr<char*>();
    simpleToArr<int>* ARR2 = new simpleToArr<int>();

    array<char*> Names = ARR1->convertFromSL(tableColumns);
    array<int> Sizes = ARR2->convertFromSL(columnsize);

    if (filesystem->createNewFile(&regSize, &Sizes, &Names, &tableName)){
        cout << "| -> Table: " << tableName << " created successfully"<<endl;
    }
}

void RegisterManager::select(string tableName, SimpleList<char *>* tableColumns){
    cout << tableName << Header->totalRegister() << " " <<tableColumns->getLenght() << endl;

    Header->resetmovingPointer();
    for (int i = 0; i<Header->totalRegister(); i++){ //general register iterator
        Header->movingPointer +=i*(*Header->registerSize); // movingPointer points at the beg of register
        if (Reg->getContentValue(Header->movingPointer) != Reg->nullChar) { //it's not empty!
            cout << "| ";
            for (int j; j<tableColumns->getLenght(); j++) { //general column iterator, writes all data
                int Col = Reg->NametoiSize(*tableColumns->elementAt(j)->getElement());
                cout << Reg->getData(Header->movingPointer+Col, Col) << " | ";
            }
            cout << endl; //end of reg
        }
    }//no break; -> check all file
    cout << "|-------------------------------------------------|" << endl;
}

void RegisterManager::select(string tableName, SimpleList<char *>* tableColumns, SimpleList<char *>* Conditions, SimpleList<int>* Booperands){
    Header->resetmovingPointer();
    for (int i = 0; i<Header->totalRegister(); i++){ //general register iterator
        Header->movingPointer +=i*(*Header->registerSize); // movingPointer points at the beg of register
        if (Reg->getContentValue(Header->movingPointer) != Reg->nullChar && Reg->check(Header->movingPointer, Conditions, Booperands)) { //it's not empty and fulfils the conditions!
            cout << "| ";
            for (int j; j<tableColumns->getLenght(); j++) { //general column iterator, writes all data
                int Col = Reg->NametoiSize(*tableColumns->elementAt(j)->getElement());
                cout << Reg->getData(Header->movingPointer+Col, Col) << " | ";
            }
            cout << endl; //end of reg
        }
    }//no break; -> check all file
    cout << "|-------------------------------------------------|" << endl;
}

void RegisterManager::insertInto(string tableName, SimpleList<char*>* tableColumns, SimpleList<char*>* values){
    simpleToArr<char*>* ARR1 = new simpleToArr<char*>();
    simpleToArr<char*>* ARR2 = new simpleToArr<int>();
    array<char*> newColumnsarr  = ARR1->convertFromSL(tableColumns);
    array<int*> newValuesArr = ARR2->convertFromSL(values);

    if(filesystem->writeNewLineToFile(tableName , newValuesArr , newColumnsarr)){
        cout << "|              Insertion successful               |" << endl;
    }else{
        cout << "|            Insertion NOT successful             |" << endl;
    }
//    Header->resetmovingPointer();
//    cout << *Header->freeRegister;
//    if (*Header->freeRegister > 0) {
//        for (int i = 0; i<Header->totalRegister(); i++){ //general register iterator, looks for a freeRegister
//            Header->movingPointer+=i*(*Header->registerSize); // movingPointer moves to the beg of register
//            if (Reg->getContentValue(Header->movingPointer)==Reg->nullChar) {//we found it!
//                for (int j; j<tableColumns->getLenght(); j++) { //general column iterator, writes all data
//                    int Col = Reg->NametoiSize(*tableColumns->elementAt(j)->getElement());
//                    Reg->setData(Header->movingPointer+Col, Col, *values->elementAt(j)->getElement());
//                }
//                Header->addRegister();
//                break;
//            }
//        }
//    } else { //there are no freeRegisters, we proceed to write at the endint
//        for (int j; j<tableColumns->getLenght(); j++) { //general column iterator, writes all data
//            int Col = Reg->NametoiSize(*tableColumns->elementAt(j)->getElement());
//            Reg->setData(Header->EndOF+Col, Col, *values->elementAt(j)->getElement());
//        }
//        Header->addRegister();
//    }
//    cout << "|              Insertion successful               |" << endl;
}

void RegisterManager::update(string tableName, SimpleList<char *>* tableColumns, SimpleList<char *>* values, SimpleList<char *>* conditions, SimpleList<int>* booperands) {
    Header->resetmovingPointer();
        for (int i = 0; i<Header->totalRegister(); i++){ //general register iterator
            Header->movingPointer+=i*(*Header->registerSize); // movingPointer points at the beg of register
            if (Reg->check(Header->movingPointer, conditions, booperands)) {//we found it!
                for (int j; j<tableColumns->getLenght(); j++) { //general column iterator, writes all data
                    int Col = Reg->NametoiSize(*tableColumns->elementAt(j)->getElement());
                    Reg->setData(Header->movingPointer+Col, Col, *values->elementAt(j)->getElement());
                }
            }
        }//no break; -> check all file
    cout << "|               Update successful                 |" << endl;
}

void RegisterManager::deleteFrom(string tableName, SimpleList<char *> *conditions, SimpleList<int>* booperands){
    Header->resetmovingPointer();
    for (int i = 0; i<Header->totalRegister(); i++){ //general register iterator
        Header->movingPointer+=i*(*Header->registerSize); // movingPointer points at the beg of register
        if (Reg->check(Header->movingPointer, conditions, booperands)) {//we found it!
            Reg->setEmpty(Header->movingPointer);
            Header->removeRegister();
        }
    }//no break; -> check all file
    cout << "|               Deletion Completed                |" << endl;
}

/*///////////////////////////////////////////////////*/

void RegisterManager::createIndexOn(string tableName, SimpleList<char *>* column, string type){
//    Header->resetmovingPointer();
//    SimpleList<char *> Nodes = SimpleList<char*>();
//    int Col = Reg->NametoiSize(column->elementAt(0)->getElement());
//    for (int i = 0; i<Header->totalRegister(); i++){ //general register iterator
//        Header->movingPointer+=i*(*Header->registerSize); // movingPointer points at the beg of register
//        if (Reg->getContentValue(Header->movingPointer) != Reg->nullChar) { //it's not empty!
//            Nodes.append(Reg->getData(Header->movingPointer+Col, Col).c_str());
//        }
//    }//no break; -> check all file
//    //BTree->Index/type, Nodes);
}

void RegisterManager::compressTable(string tableName) {
    //table selection
    cout << "|              Compression Completed              |" << endl;
}

/*////////////////////////////////////////////////*/

void RegisterManager::backupTable(string tableName){
    //table selection
    //Header->saveHeader();
    cout << "|                Backup Completed                 |" << endl;
}

void RegisterManager::restoreTable(string tableName) {
    //table selection
    //Header->loadHeader();
    cout << "|          Table Restored Successfully            |" << endl;
}
