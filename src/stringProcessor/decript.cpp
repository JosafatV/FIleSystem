#include "src/dataStructures/SimpleList.h"
#include "src/registerManager/registermanager.h"
#include "src/stringProcessor/decript.h"
#include "ErrorCodes.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

string tableName;
SimpleList<char* >* values;
SimpleList<char* >* columns;
SimpleList<char* >* conditions;
SimpleList<int>* booperands;
SimpleList<int>* val;

Decriptor::Decriptor() {
    tableName;
    *values = SimpleList<char *>();
    *conditions = SimpleList<char *>();
    *booperands = SimpleList<int>();
    val = new SimpleList<int>();
}

void Decriptor::emptyVariables() {
    tableName = "";
    values->clear();
    columns->clear();
    conditions->clear();
    booperands->clear();
}

int Decriptor::stringToInt(string* pStr){
    int i;
    i= atoi(pStr->c_str());
    return i;
}

string Decriptor::getName(string description) {
    int cut1 = description.find_first_of(' ');
    tableName = description.substr(0, cut1);
    description = description.substr(cut1, description.length());
    return description;
}

string Decriptor::getColumns(bool simpleCol, string description) {
    int cut1 = description.find_first_of('(');
    int cut2 = description.find_first_of(')');
    string temp = description.substr(cut1+1, cut2); //last parameter is from cut1 to cut2 not from 0 to cut2 - ")"
    string column;
    temp = temp.substr(0, temp.find(')'));
    if (simpleCol) {
        while (temp.length()>1) {
            cut1 = temp.find(',');
            column = temp.substr(0, cut1);
            temp = temp.substr(cut1+1, temp.length()); //cut1+1 removes ","
            columns->append((char *)column.c_str());
        }
    } else {
        string value;
        while (temp.length()>1) {
            cut1 = temp.find('<');
            column = temp.substr(0, cut1);
            temp = temp.substr(cut1+1, temp.length());
            cut1 = temp.find('>');
            value = temp.substr(0, cut1);
            temp = temp.substr(temp.find(',')+1, temp.length());
            columns->append((char *)column.c_str());
            val->append(stringToInt(&value));
        }
    }
   description = description.substr(cut2+1, description.length());
   //cout << endl;
   return description;
}

string Decriptor::getValues(string description) {
    int cut1 = description.find('(');
    int cut2 = description.find(')');
    string temp = description.substr(cut1+1, cut2);
    string value;
    temp = temp.substr(0, temp.find(')'));
    //cout << "| -> ";
    while (temp.length()>1) {
        cut1 = temp.find(',');
        value = temp.substr(0, cut1);
        temp = temp.substr(cut1+1, temp.length()); //cut1+1 removes ","
        values->append((char *)value.c_str());
        //cout << value << " - ";
    }
        //cout << temp;
    description = description.substr(cut2+1, description.length());
    //cout << endl;
    return description;
}

string Decriptor::getExpression (string temp) {
   string toGet;
   string operand;
   string value;

   string operation;
   bool flag = true;

   int cut1 = temp.find_first_of(' ');
   int cut2 = temp.length();

   toGet = temp.substr(0, cut1);
   temp = temp.substr(cut1+1, cut2);

   cut1 = temp.find_first_of(' ');
   cut2 = temp.length();

   operand = temp.substr(0, cut1);
   temp = temp.substr(cut1+1, cut2);

   cut1 = temp.find_first_of(' ');
   cut2 = temp.length();

   value = temp.substr(0, cut1);
   temp = temp.substr(cut1+1, cut2);

   if (operand==">") {
       operation=toGet+"$0%"+value;
       conditions->append((char *)operation.c_str());
       cout << operation;
       flag = false;
   }
   if (operand==">="){
       operation=toGet+"$1%"+value;
       conditions->append((char *)operation.c_str());
       cout << operation;
       flag = false;
   }
   if (operand=="<"){
       operation=toGet+"$2%"+value;
       conditions->append((char *)operation.c_str());
       cout << operation;
       flag = false;
   }
   if (operand=="<="){
       operation=toGet+"$3%"+value;
       conditions->append((char *)operation.c_str());
       cout << operation;
       flag = false;
   }
   if (operand=="="){
       operation=toGet+"$4%"+value;
       conditions->append((char *)operation.c_str());
       cout << operation;
       flag = false;
   }
   if (operand=="<>"){
       operation=toGet+"$5%"+value;
       conditions->append((char *)operation.c_str());
       cout << operation;
       flag = false;
   }
   if (flag) {
       cout << "Error002" << endl;
   }

   return temp;
}

string Decriptor::getConditions(string description) {
   int cut1 = description.find('(');
   int cut2 = description.find(')');
   string temp = description.substr(cut1+1, cut2);
   string operand;
   int operation;
   bool flag = true;

   while (temp.length()>1) {
       temp = getExpression(temp);
       if (temp.length()>1) {
           cut1 = temp.find_first_of(' ');
           operand = temp.substr(0, cut1);
           temp = temp.substr(cut1+1, temp.length());

           if (operand=="&&"){
               operation=0;
               booperands->append(operation);
               cout << " / " << operation << " / ";
               flag = false;
           }
           if (operand=="||"){
               operation=1;
               booperands->append(operation);
               cout << " / " << operation << " / ";
               flag = false;
           }
           if (flag) {
               cout << "Error003" << endl;
           }
       }
   }
   cout << endl;
   return description;
}


void Decriptor::interpreter (string* Line, int* id) {
   string command;
   string description;
   int cut = Line->find_first_of(':');
   RegisterManager* Manager;

   command = Line->substr(0, cut);
   description = Line->substr(cut+2, Line->length());

   bool flag = true;
   if (0==command.compare("CREATE TABLE")) {
       description = getName(description);
       description = getColumns(false, description);
       flag = false;
       int regSize = 0;
       for (int i = 0; i<val->getLenght(); i++){
          regSize += (*val->elementAt(i)->getElement());
       }
       Manager = new RegisterManager(tableName, columns, val, regSize);
   }
   if (0==command.compare("SELECT")) {
       if (*id == 0) {
           cut = description.find_last_of(' ');
           tableName = description.substr(cut, description.length());
           Manager->select(tableName, columns);
       }
       if (*id == 1) {
           description = getColumns(true, description);
           cut = description.find_last_of(' ');
           tableName = description.substr(cut, description.length());
           Manager->select(tableName, columns);
       }
       if (*id == 2) {
           description = getColumns(true, description);
           description = description.substr(description.find('M')+2, description.length());
           cut = description.find(' ');
           tableName = description.substr(0, cut);
           description = description.substr(cut+1, description.length());
           description = description.substr(description.find('R')+3, description.length());
           description = getConditions(description);
           Manager->select(tableName, columns, conditions, booperands);
       }

       flag = false;
   }
   if (0==command.compare("INSERT INTO")) {
       description = getName(description);
       description = getColumns(true, description);
       description = getValues(description);
       flag = false;
       cout << "HWEEEEEEEEEEREEEEEEEE";
       Manager->insertInto(tableName, columns, values);
   }
   if (0==command.compare("UPDATE")) {
       description = getName(description);
       description = getColumns(true, description);
       description = getValues(description);
       description = getConditions(description);
       flag = false;
       Manager->update(tableName, columns, values, conditions, booperands);
   }
   if (0==command.compare("DELETE FROM")) {
       description = getName(description);
       description = getConditions(description);
       flag = false;
       Manager->deleteFrom(tableName, conditions, booperands);
   }
   if (0==command.compare("CREATE INDEX ON")) {
       description = getName(description);
       description = getColumns(true, description);
       string type = description.substr(description.find_last_of(' ')+1, description.length());
       cout  << "| -> Of the type: " << type << endl;
       flag = false;
       Manager->createIndexOn(tableName, columns, type);
   }
   if (0==command.compare("COMPRESS TABLE")) {
       description = getName(description);
       flag = false;
       Manager->compressTable(tableName);
   }
   if (0==command.compare("BACKUP TABLE")) {
       description = getName(description);
       flag = false;
       Manager->backupTable(tableName);
   }
   if (0==command.compare("RESTORE TABLE")) {
       description = getName(description);
       flag = false;
       Manager->restoreTable(tableName);
   } if (flag) {
       cout << "Error001" << endl;
   }

  // emptyVariables();
}
