#include "headermanager.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;

HeaderManager::HeaderManager(int regSize)
    {
        void* buffer = malloc(headerSize);
        //name of table to recall or work it somewhere else?

        //position in header
        BOF = buffer;
        EndOF = buffer+1;
        movingPointer = buffer+2;
        //casted as int* for easier access in the program
        fullRegister = (int*)(buffer+3);
        freeRegister = (int*)(buffer+7);
        registerSize = (int*)(buffer+11);

        //value
        BOF = buffer+headerSize;
        EndOF = buffer+headerSize;
        movingPointer = buffer+headerSize;
        *registerSize = regSize;
        *fullRegister = 0;
        *freeRegister = 0;
    }

    void HeaderManager::resetmovingPointer() {
        movingPointer = BOF;
    }

    void HeaderManager::addRegister() {
        if (*freeRegister > 0) {
            *freeRegister-=1;
            *fullRegister+=1;
        } else {
            *fullRegister+=1;
            EndOF=(void*)(EndOF+*registerSize);
        }
    }

    void HeaderManager::removeRegister() {
        void* tempEndOF = (void*)(EndOF-*registerSize);

        char isEmpty = *((char*)(EndOF-*registerSize));

        if (isEmpty=='/o') {             //last register was deleted
            *fullRegister-=1;
            EndOF=(void*)(EndOF-*registerSize-1);               //resets EOF to the last register

            while (isEmpty=='/o') {
                EndOF=(void*)(EndOF-*registerSize-1);           //iterates in case there's another empty register,
                *freeRegister-=1;                           //this reduces the amount of empty registers
            }
        } else {
            *fullRegister-=1;
            *freeRegister+=1;
        }
    }

    int HeaderManager::totalRegister() {
        return *(freeRegister)+*(fullRegister);
    }
