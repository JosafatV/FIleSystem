#include "src/dataStructures/SimpleList.h"
#include "src/stringProcessor/stringprocessor.h"
#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

string Decriptor::getName(string description) {

   string tableName;

   int cut1 = description.find_first_of(' ');

   tableName = description.substr(0, cut1);
   description = description.substr(cut1, description.length());

   cout << tableName << endl;
   //cout << description << endl;

   return description;
}

string Decriptor::getColumns(bool simpleCol, string description) {
   int cut1 = description.find('(');
   int cut2 = description.find(')');
   string temp = description.substr(cut1+1, cut2); //last parameter is from cut1 to cut2 not from 0 to cut2 - ")"
   string column;
   //cout << "| -> " << temp << endl;
   if (simpleCol) {
       while (temp.length()>1) {
           cut1 = temp.find(',');
           column = temp.substr(0, cut1);
           temp = temp.substr(cut1+1, temp.length()); //cut1+1 removes ","
           cout << column << " - ";
       }
   } else {
       string value;
       while (temp.length()>1) {
           cut1 = temp.find('<');
           column = temp.substr(0, cut1);
           value = temp.substr(cut1+1, temp.find('>')); //cut1+1 removes "<"
           temp = temp.substr(temp.find(',')+1, temp.length());
           cout << column << "/" << value << " - ";
       }
   }
   description = description.substr(cut2+1, description.length());
   cout << endl;
   return description;
}

string Decriptor::getValues(string description) {
   int cut1 = description.find('(');
   int cut2 = description.find(')');
   string temp = description.substr(cut1+1, cut2-cut1-1); //last parameter is from cut1 to cut2 not from 0 to cut2 - ")"
   string column;
   //SimpleList values = new SimpleList();
   //cout << "| -> " << temp << endl;
   cout << "| -> ";
   while (temp.length()>1) {
       cut1 = temp.find(',');
       column = temp.substr(0, cut1);
       temp = temp.substr(cut1+1, temp.length()); //cut1+1 removes ","
       //values.append();
       cout << column << " - ";
   }
   cout << endl;
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

   cout << toGet;

   if (operand==">") {
       operation="0"+value;
       //conditions.append(operation);
       cout << operation;
       flag = false;
   }
   if (operand==">="){
       operation="1"+value;
       //conditions.append(operation);
       cout << operation;
       flag = false;
   }
   if (operand=="<"){
       operation="2"+value;
       //conditions.append(operation);
       cout << operation;
       flag = false;
   }
   if (operand=="<="){
       operation="3"+value;
       //conditions.append(operation);
       cout << operation;
       flag = false;
   }
   if (operand=="="){
       operation="4"+value;
       //conditions.append(operation);
       cout << operation;
       flag = false;
   }
   if (operand=="<>"){
       operation="5"+value;
       //conditions.append(operation);
       cout << operation;
       flag = false;
   }
   if (flag) {
       cout << "ERROR 002: Operand missing or not defined" << endl;
   }

   return temp;
}

string Decriptor::getConditions(string description) {
   //SimpleList toGetValue = new SimpleList();
   //SimpleList conditions = new SimpleList();
   //SimpleList booperands = new SimpleList();
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
           temp = temp.substr(cut1+1, cut2);

           if (operand=="&&"){
               operation=0;
               //booperands.append(operation);
               cout << " / " << operation << " / ";
               flag = false;
           }
           if (operand=="||"){
               operation=1;
               //booperands.append(operation);
               cout << " / " << operation << " / ";
               flag = false;
           }
           if (flag) {
               cout << "ERROR 003: Boolean operand not recognized" << endl;
           }

       }
   }
   cout << endl;
   return description;
}


void Decriptor::interpreter (string Line, int id) {

   string command;
   string description;
   string tableName;
   int cut = Line.find_first_of(':');

   command = Line.substr(0, cut);
   description = Line.substr(cut+2, Line.length());

   //cout << "| -> " << command << endl;
   //cout << "| -> ";

   bool flag = true;
   if (0==command.compare("CREATE TABLE")) {
       description = getName(description);
       description = getColumns(false, description);
       flag = false;
   }
   if (0==command.compare("SELECT")) {
       if (id == 0) {
           cut = description.find_last_of(' ');
           tableName = description.substr(cut, description.length());
           cout << tableName << endl;
           cout << "| -> " << "all columns" << endl;
       }
       if (id == 1) {
           description = getColumns(true, description);
           cut = description.find_last_of(' ');
           tableName = description.substr(cut, description.length());
           cout << tableName;
       }
       if (id == 2) {
           description = getColumns(true, description);
           cut = description.find(' ');
           tableName = description.substr(cut, description.find_first_of(' ', cut+1));
           description = description.substr(description.find_last_of('('), description.find_last_of(')'));
           description = getConditions(description);
           cout << tableName;
       }
       flag = false;
   }
   if (0==command.compare("INSERT INTO")) {
       description = getName(description);
       description = getColumns(1, description);
       description = getValues(description);
       flag = false;
   }
   if (0==command.compare("UPDATE")) {
       description = getName(description);
       description = getColumns(0, description);
       description = getValues(description);
       description = getConditions(description);
       flag = false;
   }
   if (0==command.compare("DELETE FROM")) {
       description = getName(description);
       flag = false;
   }
   if (0==command.compare("CREATE INDEX ON")) {
       description = getName(description);
       string type = description.substr(description.find_last_of(' '), description.length());
       cout  << "| -> Of the type: " << type;
       flag = false;
   }
   if (0==command.compare("COMPRESS TABLE")) {
       description = getName(description);
       flag = false;
   }
   if (0==command.compare("BACKUP TABLE")) {
       description = getName(description);
       flag = false;
   }
   if (0==command.compare("RESTORE TABLE")) {
       description = getName(description);
       flag = false;
   } if (flag) {
       cout << "ERROR 001: Command not defined" << endl;
   }
}
