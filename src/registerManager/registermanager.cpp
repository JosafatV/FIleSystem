#include "src/registerManager/registermanager.h"
#include "src/HeaderManager/headermanager.h"
#include "src/dataStructures/SimpleList.h"
#include "src/Register/register.h"
#include "src/stringProcessor/decriptor.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>


using namespace std;

HeaderManager* Header;
Register* Reg;

RegisterManager::RegisterManager (string tableName, SimpleList<char *> *tableColumns, SimpleList<int>* columnsize, int regSize) {
    //table creation
    Header = new HeaderManager(regSize);
    Reg = new Register(tableColumns, columnsize);
    cout << "| -> Table: " << tableName << " created successfully";
}

void RegisterManager::select(string tableName, SimpleList<string*>* tableColumns, SimpleList<string*>* Conditions, SimpleList<int>* Booperands){
    //table selection
    Header->resetmovingPointer();
    int totalRegisters = Header->totalRegister();
    for (int i = 0; i<=totalRegisters; i++) {
        if (checkCondition(Conditions, Booperands)) {  //checks if any condition set by the user apply in register(i)
            for (int i = 0; i<tableColumns.getLenght(); i++) {
                cout << Reg->getData(movingPointer, Reg->NametoiSize(tableColumns->elementAt(i)->getElement())) << " - ";
            }
            cout << endl;
        }
    }
}

void RegisterManager::insertInto(string tableName, SimpleList<string*>* tableColumns, SimpleList<string*>* values){
    //table selection
    int i = 0;
    for (int j = 0; j<tableColumns->getLenght(); j++) {
        if (*(Header->freeRegister) > 0) {
            Header->resetmovingPointer();
            while (Register.getContentValue((Header->movingPointer)+i) == Register->nullChar) {       // conseguir el registro vacio (first char == nullChar --> empty)
                i+=Header->registerSize;
            }
            Register::setData(movingPointer, Reg->NametoiSize(tableColumns.elementAt(j)->getElement()), value(Reg->NametoiSize(tableColumns.elementAt(j)->getElement())));
            Header->addRegister();
        } else {
            Register::setData(movingPointer, Reg->NametoiSize(tableColumns.elementAt(j)->getElement()), value(Reg->NametoiSize(tableColumns.elementAt(j)->getElement())));
            writeHere(Header->EOF);
            Header->addRegister();
        }
    }
    cout << "|              Insertion successful               |" << endl;
}

void RegisterManager::update(string tableName, SimpleList<string*>* tableColumns, SimpleList<string*>* values, SimpleList<string*>* conditions, SimpleList<int>* booperands) {
    //table selection
    Header->resetmovingPointer();
    if (conditions.size()==0) {
        for (int i = 0; i<=totalRegisters; i++) {
            Reg->setData(Reg->NametoiSize(tableColumns.elementAt(i)->getElement()), values(i));
        }
    } else {
        for (int i = 0; i<=totalRegisters; i++) {
            if (checkCondition(Conditions, Booperands)) {
                Reg->setData(Reg.Reg->NametoiSize(tableColumns.elementAt(i)->getElement()), values(i));
            }
        }
    }
    cout << "|               Update successful                 |" << endl;
}

void RegisterManager::deleteFrom(string tableName, SimpleList<string*>* conditions, SimpleList<int>* booperands){
    //table selection
    Header->resetmovingPointer();
    int totalRegisters = Header->totalRegister();
    for (int i = 0; i<=totalRegisters; i++) {
        if (checkCondition(Conditions, Booperands)) {  //~checks if any condition set by the user apply in register(i)
            Reg->setEmpty((Header->movingPointer)+i*Header->registerSize);
            Header->removeRegister();  //manages multiple eliminations from EOF
        }
    }
    cout << "|               Deletion Completed                |" << endl;
}

/*///////////////////////////////////////////////////*/

void RegisterManager::createIndexOn(string tableName, SimpleList<string*>* column, string type){
    //table selection
//    int iColumn = Reg.ColumnNametoColumnSize(column);
//    for (int i = 0; i<Header.registerSize; i++){
//        //BinaryTree.start(type);
//        //BinaryTree.add(Register.getData(iColumn));
//    }
}

void RegisterManager::compressTable(string tableName) {
    //table selection
    cout << "|              Compression Completed              |" << endl;
}

/*////////////////////////////////////////////////*/

void RegisterManager::backupTable(string tableName){
    //table selection
    Header->saveHeader();
    cout << "|                Backup Completed                 |" << endl;
}

void RegisterManager::restoreTable(string tableName) {
    //table selection
    Header->loadHeader();
    cout << "|          Table Restored Successfully            |" << endl;
}
