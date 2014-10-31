#include "src/dataStructures/SimpleList.h"
#include "src/stringProcessor/decript.h"
#include "src/HeaderManager/headermanager.h"
#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

void testDecript() {
    Decriptor* decript = new Decriptor();

    string test1 = "CREATE TABLE: tableName (columnaN<LenghtA>, columnaM<LenghtB>,)";
    string test2 = "SELECT: * FROM tableName";
    string test2a = "SELECT: (columnaN, columnaM,) FROM tableName";
    string test2b = "SELECT: (columnaN, columnaM,) FROM tableName WHERE (Condition <= Value && ConditionB <> ValueB )";
    string test3 = "INSERT INTO: tableName SET (columnaN, columnaM,) VALUES (ValueA, ValueB,)";
    string test4 = "UPDATE: tableName SET (columnaN, columnaM,) VALUES (ValueA, ValueB,) WHERE (Condition <= Value && ConditionB <> ValueB )";
    string test5 = "DELETE FROM: tableName WHERE (Condition <= Value && ConditionB <> ValueB )";
    string test6 = "CREATE INDEX ON: tableName (columnaM,) TYPE B+";
    string test7 = "COMPRESS TABLE: tableName ";
    string test8 = "BACKUP TABLE: tableName ";
    string test9 = "RESTORE TABLE: tableName ";

//    decript->interpreter(test1, 0);       //working
//    decript->interpreter(test2, 0);       //working
//    decript->interpreter(test2a, 1);      //working
//    decript->interpreter(test2b, 2);      //working
//    decript->interpreter(test3, 0);       //workong
//    decript->interpreter(test4, 0);       //working
//    decript->interpreter(test5, 0);       //working
//    decript->interpreter(test6, 0);       //working
//    decript->interpreter(test7, 0);       //not yet implemented
//    decript->interpreter(test8, 0);       //working
//    decript->interpreter(test9, 0);       //working

    string testA = "(Condition <= Value )";
    string testB = "(Condition = Value || Condition2 <> Value2 )";
    string testC = "(Condition < Value && Condition2 > Value2 || Condition >= Value && Condition2 <= Value2 )";
    string testD = "(Value1, Value2, Value3, Value4, ValueN,)";

//    cout << getConditions(testA);
//    cout << getConditions(testB);
//    cout << getConditions(testC);
//    cout << getValues(testD);
}

void testHeader () {

    HeaderManager* Header = new HeaderManager(50);

    cout << " _________________________________________________ " << endl
         << "|          Welcome to the Header Manager          |" << endl
         << "|*************************************************|" << endl
         << "|                Creating Header...               |" << endl;
    cout << "| -> " << Header->headerSize <<endl;
    cout << "| -> " << Header->BOF << endl;
    cout << "| -> " << Header->EndOF << endl;
    cout << "| -> " << *(Header->freeRegister) << endl;
    cout << "| -> " << *(Header->fullRegister) << endl;
    cout << "| -> " << *(Header->registerSize) << endl;
    cout << "|               Adding Register...               |" << endl;
    Header->addRegister();
    cout << "| -> " << Header->EndOF << endl;
    cout << "| -> " << *(Header->freeRegister) << endl;
    cout << "| -> " << *(Header->fullRegister) << endl;
    cout << "|               Adding Register...               |" << endl;
    Header->addRegister();
    cout << "| -> " << Header->EndOF << endl;
    cout << "| -> " << *(Header->freeRegister) << endl;
    cout << "| -> " << *(Header->fullRegister) << endl;
    cout << "|              Removing Register...              |" << endl;
    Header->removeRegister();
    cout << "| -> " << Header->EndOF << endl;
    cout << "| -> " << *(Header->freeRegister) << endl;
    cout << "| -> " << *(Header->fullRegister) << endl;
    cout << "|           Register Quanity:" << Header->totalRegister() << endl;
    cout << "|               Adding Register...                |" << endl;
    Header->addRegister();
    cout << "| -> " << Header->EndOF << endl;
    cout << "| -> " << *(Header->freeRegister) << endl;
    cout << "| -> " << *(Header->fullRegister) << endl;
    cout << "|               Adding Register...               |" << endl;
    Header->addRegister();
    cout << "| -> " << Header->EndOF << endl;
    cout << "| -> " << *(Header->freeRegister) << endl;
    cout << "| -> " << *(Header->fullRegister) << endl;

}

int main()
{
    cout << " _________________________________________________ " << endl
         << "|          Welcome to the MyFSQL - server         |" << endl
         << "|*************************************************|" << endl
         << "| -> ";

    bool running = true;
    string line;
    int type=0;
    while (running) {
        getline (cin, line);
        if (line == "EXIT"){
            running = false;
        if (line == ""){
            cout << endl;
        }
        } else {
            Decriptor* execute = new Decriptor;
            execute->interpreter(&line, &type);
        }
        line="";
        cout << "| -> ";
    }
    cout << "|              - EXITING PROGRAM -                |" << endl;
    cout << "|______________________***________________________|" << endl;

    return 0;
}
