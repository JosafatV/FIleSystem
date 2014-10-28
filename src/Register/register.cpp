#include "register.h"
#include "src/HeaderManager/headermanager.h"
#include "ErrorCodes.h"

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;

Register::Register()
{
}

void Register::setEmpty (void* Here) {
    char* isEmpty = (char*) Here;
    *isEmpty = nullChar;
}

char Register::getContentValue(void* Here) {
    char* Value = (char*) Here;
    return *Value;
}

/*reads data from a single object in a single column
 * use in iteration
 *
 */
string Register::getData(void* Here, int iColumn) {
    int beg = ColumnSize<iColumn>;
    int end = ColumnSize<iColumn+1>;
    for (beg <= end; beg++;) {               //change to print chars until '/o'
        cout << *( (char*)Here );
    }
}

string Register::setData(void* Here, int iColumn, string Value) {
    char* writePoiner = (char *)Here;
    int beg = ColumnSize<iColumn>;
    int end = ColumnSize<iColumn+1>;
    if (Value.size()<(end-beg)) {
    for (beg <= end; beg++;) {               //check lenght of string
        writePoiner += beg;
        *writePointer = Value;
    }
    } else {
        cout << Error004 << endl;
    }
}

int Register::ColumnNametoColumnSize (string Name) {
    for (int i = 0; i<ColumnName.size(); i++) {
        if (ColumnName(i)==Name) {
            return i;
        }
    }
}
