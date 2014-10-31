#ifndef REGISTERMANAGER_H
#define REGISTERMANAGER_H
#include <string>
#include "src/dataStructures/SimpleList.h"
#include "src/HeaderManager/headermanager.h"
#include "src/Register/register.h"
#include "fsqlserverfilesystem.h"

class RegisterManager
{
public:
    /*!
     * \brief RegisterManager - it makes an instance of a header without registers
     * \param tableName - the name by which the file will be recognized
     * \param tableColumns - the name of the columns, in order, that compose the file
     * \param columnsize - the size, in bytes, of the each column, in order
     * \param regSize - the sum of the size of the columns, ie, the size of the register
     *
     * It instances the header, creating the file. In this step the program gathers all the information that will require later. This cannot be modified.
     */
    RegisterManager(string tableName, SimpleList<char *> *tableColumns, SimpleList<int>* columnsize, int regSize);


    /*!
     * \brief RegisterManager::select - prints the selected values
     * \param tableName - the name by which the file will be recognized
     * \param tableColumns - the name of the columns, in order, that compose the file
     *
     * It prints all the available data from the columns especified
     */
    void select(string tableName, SimpleList<char *>* tableColumns);

    /*!
     * \brief RegisterManager::select - prints the selected values
     * \param tableName - the name by which the file will be recognized
     * \param tableColumns - the name of the columns, in order, that compose the file
     * \param conditions - a special list that holds the value of the comparator and the value to which the entry will be compared to
     * \param booperands - a list with the boolean operands for the comparison
     *
     * Selects from the columns entered ("*" means all of them) and optionally compares the value of the register to given conditions to get more precise info
     * It will only print the columns given, the parameters measured in the conditions can range outside the printed columns
     */
    void select(string tableName, string columnName, SimpleList<char *>* Conditions, SimpleList<int>* Booperands);

    /*!
     * \brief RegisterManager::insertInto - adds registers
     * \param tableName - the name by which the file will be recognized
     * \param tableColumns - the name of the columns, in order, that compose the file
     * \param values - the values that the register will have when created
     */
    void insertInto(string tableName, SimpleList<char *>* tableColumns, SimpleList<char *>* values);

    /*!
     * \brief RegisterManager::update - updates values inside the file
     * \param tableName - the name by which the file will be recognized
     * \param tableColumns - the name of the columns, in order, that compose the file
     * \param values - the values that the register will have when updated
     * \param conditions - a special list that holds the value of the comparator and the value to which the entry will be compared to
     * \param booperands - a list with the boolean operands for the comparison
     */
    void update(string tableName, SimpleList<char *> *tableColumns, SimpleList<char *> *values);

    /*!
     * \brief RegisterManager::deleteFrom - deletes entire registers if they fulfil the conditions
     * \param tableName - the name by which the file will be recognized
     * \param conditions - a special list that holds the value of the comparator and the value to which the entry will be compared to
     * \param booperands - a list with the boolean operands for the comparison
     */
    void RegisterManager::deleteFrom(string tableName, string pColumnName, string pData);

    /*!
     * \brief RegisterManager::createIndexOn - indexes a column
     * \param tableName - the name by which the file will be recognized
     * \param column - the column that will be indexed
     * \param type . the type of tree that will be used when indexing
     *
     * Indexing changes the way the program gets info allowing for faster searches in said column. It achieves this by indexing the column in a B tree
     */
    void createIndexOn(string tableName, SimpleList<char *> *column, string type);

    /*!
     * \brief RegisterManager::compressTable - removes all the empty registers
     * \param tableName - the name by which the file will be recognized
     *
     * This function compresses the registers by eliminating the free registers lowering the size of the file. In this process the old registers are overwritten by the other registers
     */
    void compressTable(string tableName);

    /*!
     * \brief RegisterManager::backupTable - makes a copy of the file
     * \param tableName - the name by which the file will be recognized
     *
     * This function duplicates the file and loads into a SDcard through an arduino
     */
    void backupTable(string tableName);

    /*!
     * \brief RegisterManager::restoreTable - restores a file
     * \param tableName - the name by which the file will be recognized
     *
     * This function duplicates the file and loads into a SDcard through an arduino
     */
    void restoreTable(string tableName);

    void createHardTable(string tableName,SimpleList<char *>* tableColumns,
                         SimpleList<int>* columnsize,int regSize);

private:
    HeaderManager* Header;
    Register* Reg;
    FSQLServerFileSystem* filesystem;

};

#endif // REGISTERMANAGER_H
