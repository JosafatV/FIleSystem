#include "register.h"
#include "src/HeaderManager/headermanager.h"
#include "ErrorCodes.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;

SimpleList<char*>* ColumnName;
SimpleList<int>* ColumnSize;

Register::Register(SimpleList<char *>* tableColumns, SimpleList<int>* columnSizes)
{
    ColumnName = new SimpleList<char *>();
    ColumnSize = new SimpleList<int>();

    ColumnSize->append(0);
    for (int i = 0; i<tableColumns->getLenght(); i++) {
        ColumnName->append((*tableColumns->elementAt(i)->getElement()).c_str());
        ColumnSize->append(*columnSizes->elementAt(i)->getElement());
    }

}

/* Changes the first char to an especific "nullChar" in order to mark the register as empty
 *
 */
void Register::setEmpty (void* Here) {
    char* isEmpty = (char *) Here;
    *isEmpty = nullChar;
}

/* get the value of the first char to know if the register is empty
 *
 */
char Register::getContentValue(void* Here) {
    char* Value = (char *) Here;
    return *Value;
}

/*reads data from a single object in a single column
 * use in iteration
 *
 */
string Register::getData(void* Here, int iColumn) {
    string Data;
    int beg = *ColumnSize->elementAt(iColumn)->getElement();
    int end = *ColumnSize->elementAt(iColumn+1)->getElement();
    for (beg < end; beg++;) {
        cout << (char*)Here;    //prints chars until '/o' or until the end of the column
        Data += (char*)Here;
    }
    return Data;
}

void Register::setData(void* Here, int iColumn, string Value) {
    const char* writePointer = (char *)Here;
    int beg = *ColumnSize->elementAt(iColumn)->getElement();
    int end = *ColumnSize->elementAt(iColumn+1)->getElement();
    if (Value.length()<(end-beg)) {//check lenght of string
        for (beg <= end; beg++;) {
            writePointer += beg;
            writePointer = Value.c_str();  //writes each char?
        }
    } else {
        cout << Error004 << endl;
    }
}

int Register::NametoiSize (string Name) {
    int index = -1;
    for (int i = 0; i<ColumnName->getLenght(); i++) {
        if (*ColumnName->elementAt(i)->getElement()==Name) {
            index = i;
            break;
        }
    }
    return index;
}

bool Register::checkAux(void* Here, SimpleList<char *>* conditions, int i) {
    string Expression = *conditions->elementAt(i)->getElement();
    string toGet = Expression.substr(0, Expression.find('$'));
    Expression=Expression.substr(Expression.find('$')+1, Expression.length());
    int Operand = (int)(Expression.substr(0, Expression.find('%')));
    Expression=Expression.substr(Expression.find('%')+1, Expression.length());
    string Value=Expression;

    string Base = getData(Here, NametoiSize(toGet));

    bool Res = false;
    switch (Operand) {
    case 0: Res = (Base >  Value); break;
    case 1: Res = (Base >= Value); break;
    case 2: Res = (Base <  Value); break;
    case 3: Res = (Base <= Value); break;
    case 4: Res = (Base == Value); break;
    case 5: Res = (Base != Value); break;
    }
    return Res;
}

//it needs to check the entire register
bool Register::check(void* Here, SimpleList<char *>* conditions, SimpleList<int>* booperands) {
    bool Res = false;
    bool Res2 = false;
    Res = checkAux(Here, conditions, 0);
    for (int i = 1; i<=booperands->getLenght(); i++) {
        Res2 = checkAux(Here, conditions, i);
        switch((int)(*booperands->elementAt(i)->getElement())) {
        case 1: Res = (Res && Res2); break;
        case 2: Res = (Res || Res2); break;
        }
    }
    return Res; //yay!
}
