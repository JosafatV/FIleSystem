#ifndef HEADERMANAGER_H
#define HEADERMANAGER_H

class HeaderManager
{
public:
    HeaderManager(int regSize);
    void saveHeader();
    void loadHeader();

    int headerSize = 3*sizeof(int)+3*sizeof(char);

    void* BOF;
    void* EndOF;
    void* pRegister;
    void* pfreeRegister;
    void* movingPointer;
    int* Register;
    int* freeRegister;
    int* registerSize;        //size of Register in bytes

    void addRegister();
    void removeRegister();
    int totalRegister();
    void resetmovingPointer();
};

#endif // HEADERMANAGER_H
