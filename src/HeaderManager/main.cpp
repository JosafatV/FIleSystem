#include "headermanager.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main()
{

    cout << " _________________________________________________ " << endl
         << "|          Welcom to the Header Manager           |" << endl
         << "|*************************************************|" << endl
         << "|                Creating Header...               |" << endl;

    HeaderManager* Header = new HeaderManager(50);
    cout << "| -> " << Header->headerSize <<endl;
    cout << "| -> " << Header->BOF << endl;
    cout << "| -> " << Header->EndOF << endl;
    cout << "| -> " << *(Header->freeRegister) << endl;
    cout << "| -> " << *(Header->fullRegister) << endl;
    cout << "| -> " << *(Header->registerSize) << endl;

  cout << "|            Adding Register...            |" << endl;
    Header->addRegister();

    cout << "| -> " << Header->EndOF << endl;
    cout << "| -> " << *(Header->freeRegister) << endl;
    cout << "| -> " << *(Header->fullRegister) << endl;

  cout << "|            Adding Register...            |" << endl;
    Header->addRegister();

    cout << "| -> " << Header->EndOF << endl;
    cout << "| -> " << *(Header->freeRegister) << endl;
    cout << "| -> " << *(Header->fullRegister) << endl;

  cout << "|           Removing Register...            |" << endl;
    Header->removeRegister();

    cout << "| -> " << Header->EndOF << endl;
    cout << "| -> " << *(Header->freeRegister) << endl;
    cout << "| -> " << *(Header->fullRegister) << endl;


  cout << "|           Register Quanity:" << Header->totalRegister() << endl;

  cout << "|            Adding Register...            |" << endl;
    Header->addRegister();

    cout << "| -> " << Header->EndOF << endl;
    cout << "| -> " << *(Header->freeRegister) << endl;
    cout << "| -> " << *(Header->fullRegister) << endl;

    cout << "|            Adding Register...            |" << endl;
      Header->addRegister();

      cout << "| -> " << Header->EndOF << endl;
      cout << "| -> " << *(Header->freeRegister) << endl;
      cout << "| -> " << *(Header->fullRegister) << endl;

    return 0;
}

