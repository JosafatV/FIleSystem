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

RegisterManager::RegisterManager () {

}

void RegisterManager::createTable(string tableName, SimpleList tableColumns, SimpleList columnsize, int regSize) {
    //table creation
    HeaderManager Header = new HeaderManager(regSize);
    int spaces = tableName.length();
    cout << "| -> Table: " << tableName << " created successfully";
    for (int i = 0; i<spaces; i++) {
        cout << " ";
    }
    cout << endl;
}

void RegisterManager::select(string tableName, SimpleList tableColumns, SimpleList Conditions, SimpleList Booperands){
    //table selection
    HeaderManager.resetmovingPointer();
    int totalRegisters = HeaderManager.totalRegister();
    for (int i = 0; i<=totalRegisters; i++) {
        if (checkCondition(Conditions, Booperands)) {  //checks if any condition set by the user apply in register(i)
            for (int i = 0; i<tableColumns.size(); i++) {
                cout << Register.getData(Register.ColumnNametoColumnSize(tableColumns(i))) << " - ";
            }
            cout << endl;
        }
    }
}

void RegisterManager::insertInto(string tableName, SimpleList tableColumns, SimpleList values){
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
    cout << "|              Insertion successful               |" << endl;
}

void RegisterManager::update(string tableName, SimpleList tableColumns, SimpleList values, SimpleList conditions, SimpleList Boopeands) {
    //table selection
    HeaderManager.resetmovingPointer();
    if (conditions.size()==0) {
        for (int i = 0; i<=totalRegisters; i++) {
            Register.setData(Register.ColumnNametoColumnSize(tableColumns(i)), values(i));
        }
    } else {
        for (int i = 0; i<=totalRegisters; i++) {
            if (checkCondition(Conditions, Booperands)) {
                Register.setData(Register.ColumnNametoColumnSize(tableColumns(i)), values(i));
            }
        }
    }
    cout << "|               Update successful                 |" << endl;
}

void RegisterManager::deleteFrom(string tableName, SimpleList Conditions, SimpleList Booperands){
    //table selection
    HeaderManager.resetmovingPointer();
    int totalRegisters = HeaderManager.totalRegister();
    for (int i = 0; i<=totalRegisters; i++) {
        if (checkCondition(Conditions, Booperands)) {  //~checks if any condition set by the user apply in register(i)
            Register.setEmpty((HeaderManager.movingPointer)+i*HeaderManager.registerSize);
            HeaderManager.removeRegister();  //manages multiple eliminations from EOF
        }
    }
    cout << "|               Deletion Completed                |" << endl;
}

/*///////////////////////////////////////////////////*/

void RegisterManager::createIndexOn(string tableName, string column, string type){
    //table selection
    int iColumn = Register.ColumnNametoColumnSize(column);
    for (int i = 0; i<HeaderManager.registerSize; i++){
        BinaryTree.start(type);
        BinaryTree.add(Register.getData(iColumn));
    }
}

void RegisterManager::compressTable(string tableName) {
    //table selection
    cout << "|              Compression Completed              |" << endl;
}

/*////////////////////////////////////////////////*/

void RegisterManager::backupTable(string tableName){
    //table selection
    HeaderManager.saveHeader(tableName);
    cout << "|                Backup Completed                 |" << endl;
}

void RegisterManager::restoreTable(string tableName){
    //table selection
    HeaderManager.loadHeader(tableName);
    cout << "|          Table Restored Successfully            |" << endl;
}
