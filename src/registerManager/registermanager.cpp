#include "registermanager.h"
#include "headermanager.h"
#include "SimpleList/SimpleList.h"
#include "register.h"
#include "sintaxdecripter.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;


//checkCondition(conditions)


void RegisterManager::createTable(string tableName, string<>tableColumns, int<> columnsize, int regSize) {
    //table selection
    HeaderManager Header = new HeaderManager(int regSize);
    cout << "Table: " << tableName << " created successfully" << endl;
}


void RegisterManager::select(string tableName, string<> tableColumns, string<> Conditions){
    //table selection
    HeaderManager.resetmovingPointer();
    int totalRegisters = HeaderManager.totalRegister();
    for (int i = 0; i<=totalRegisters; i++) {
        if (checkCondition(conditions)) {  //checks if any condition set by the user apply in register(i)
            for (int i = 0; i<tableColumns.size(); i++) {
                cout << Register.getData(Register.ColumnNametoColumnSize(tableColumns(i))) << " - ";
            }
            cout << endl;
        }
    }
}


void RegisterManager::insertInto(string tableName, string<> tableColumns, string<> values){
    //table selection
    int i = 0;
    for (int j = 0; j<tableColumns.length(); j++) {
        if (*(HeaderManager.freeRegister) > 0) {
            HeaderManager.resetmovingPointer();
            while (Register.getContentValue((HeaderManager.movingPointer)+i) == nullChar) {       // conseguir el registro vacio (first char == nullChar --> empty)
                i+=HeaderManager.registerSize;
            }
            Register::setData(movingPointer, Register.ColumnNametoColumnSize(tableColumns<j>), value(Register.ColumnNametoColumnSize(tableColumns<j>)));
            HeaderManager.addRegister();
        } else {
            Register::setData(movingPointer, Register.ColumnNametoColumnSize(tableColumns<j>), value(Register.ColumnNametoColumnSize(tableColumns<j>)));
            writeHere(HeaderManager.EOF);
            HeaderManager.addRegister();
        }
    }
    cout << "Insertion successful" << endl;
}


void RegisterManager::update(string tableName, string<> tableColumns, string<> values, string<> conditions) {
    //table selection
    HeaderManager.resetmovingPointer();
    if (conditions.size()==0) {
        for (int i = 0; i<=totalRegisters; i++) {
            Register.setData(Register.ColumnNametoColumnSize(tableColumns(i)), values(i));
        }
    } else {
        for (int i = 0; i<=totalRegisters; i++) {
            if (sintaxDecripter.compare(Register.getData(i), conditions(i))) {//~
                Register.setData(Register.ColumnNametoColumnSize(tableColumns(i)), values(i));
            }
        }
    }
    cout << "Update successful" << endl;
}


void RegisterManager::deleteFrom(string tableName, string<> conditions){
    //table selection
    HeaderManager.resetmovingPointer();
    int totalRegisters = HeaderManager.totalRegister();
    for (int i = 0; i<=totalRegisters; i++) {
        if (sintaxDecripter.compare(Register.getData(i), conditions(i))) {  //~checks if any condition set by the user apply in register(i)
            Register.setEmpty((HeaderManager.movingPointer)+i*HeaderManager.registerSize);
            HeaderManager.removeRegister();  //manages multiple eliminations from EOF
        }
     }
}

/*///////////////////////////////////////////////////*/

void RegisterManager::createIndexOn(string tableName, string column, string type){
    //table selection
    string iColumn = Register.ColumnNametoColumnSize(column);
    for (int i = 0; i<HeaderManager.registerSize; i++){
        BinaryTree.add(Register.getData(iColumn));
    }
}

void RegisterManager::compressTable(string tableName) {
    //table selection

}

/*////////////////////////////////////////////////*/

void RegisterManager::backupTable(string tableName){
    HeaderManager.saveHeader(tableName);
}

void RegisterManager::restoreTable(string tableName){
    HeaderManager.loadHeader(tableName);
}
