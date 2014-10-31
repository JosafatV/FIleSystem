#ifndef REGISTER_H
#define REGISTER_H
#include <string>
#include "src/dataStructures/SimpleList.h"
using namespace std;

class Register
{
public:
    Register(SimpleList<char *>* tableColumns, SimpleList<int>* columnsizes);

    /*!
     * \brief ColumnName is a simple list with the name of the columns
     * This global variable helps the program traducing the strings that the user inputs into integers that are more manageable
     */
    SimpleList<char*>* ColumnName = new SimpleList<char*> ();

    /*!
     * \brief ColumnSize is a simple list with the values of the size of columns
     * This global variable always starts on 0 and helps the program manage the movingPointer position "in the X coordinate" (Y being the registers), in order to get individual sets of data
     */
    SimpleList<int>* ColumnSize = new SimpleList<int>  ();

    /*!
     * \brief nullChar marks a register as empty
     * This char is especially chosen by the project to be a mark at the beggining of the register (or column) to mark it as empty, it doesn't allow the first value to be removed
     */
    char nullChar = '*';

    /*!
     * \brief setEmpty writes a nullChar here, it sets the Register space as empty
     * \param Here the pinter that points to the byte to be changed
     */
    void setEmpty (void* Here);

    /*!
     * \brief getData reads data from a single object in a single column, use in iteration
     * \param Here the pointer that points to the beginning of the space  that will be read
     * \param iColumn the index of the column from were the data is read
     * \return the data read by this method
     */
    string getData(void* Here, int iColumn);

    /*!
     * \brief setData writes data from the pointer Here to the end of the data previously sized
     * \param Here the pointer that points to the beginning of the writting space
     * \param iColumn the index of the column were it will be written
     * \param Value the string that will be written
     */
    void setData(void* Here, int iColumn, string Value);

    /*!
     * \brief NametoiSize converts the name of a column to the index of it's respective matrix
     * \param Name name of the column
     * \return the index (int)
     */
    int NametoiSize (string Name);

    /*!
     * \brief getContentValue checks if a register is empty
     * \param Here the position of the first char
     * \return the char so it an be compared to nullChar
     *
     * With this function the programs gets the first charactr of a register in order to know if that register is empty or has data
     */
    char getContentValue(void* Here);

    /*!
     * \brief checkAux
     * \param Here
     * \param conditions
     * \param i
     */
    bool checkAux(void* Here, SimpleList<char *>* conditions, int i);

    /*!
     * \brief check
     * \param conditions
     * \param booperands
     */
    bool check(void *Here, SimpleList<char *>* conditions, SimpleList<int>* booperands);
};

#endif // REGISTER_H
