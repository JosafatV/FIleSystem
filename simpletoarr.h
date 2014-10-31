#ifndef SIMPLETOARR_H
#define SIMPLETOARR_H
#include "src/dataStructures/SimpleList.h"
#include "array/array.h"
#include "konstants.h"

template <typename K>
class simpleToArr
{
public:
    simpleToArr();
    array<K > convertFromSL(SimpleList<K>* pSLToConvert);
    konstants* C;
};

template <typename K>
simpleToArr<K>::simpleToArr(){
    C = new konstants();
}

template <typename K>
array<K> simpleToArr<K>::convertFromSL(SimpleList<K>* pSLToConvert){
    int lenght = pSLToConvert->getLenght();
    array<K> arrToreturn (lenght);
    if(lenght == C->ZE_ROW) {
        return arrToreturn;
    }

    SimpleListNode<K>* tempH = pSLToConvert->getHead();
    for (int i = C->ZE_ROW ; i < lenght ;i++){
        arrToreturn[i] = *tempH->getElement();
        tempH = tempH->getNext();
    }
    return arrToreturn;
}

#endif // SIMPLETOARR_H
