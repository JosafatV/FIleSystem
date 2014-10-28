#ifndef HEADERMANAGER_H
#define HEADERMANAGER_H

class HeaderManager
{
public:
    HeaderManager(int regSize);
    void saveHeader();
    void loadHeader();

    int headerSize = 3*sizeof(int)+3*sizeof(char);

    /*!
     * \brief BOF points to the beggining of the file
     * This points to the beggining of the first register, not the beggining of the header
     */
    void* BOF;

    /*!
     * \brief EndOF points to the end of the file;
     * this points to the end of the last register if you rest the register size you get to the beggining of the last register
     */
    void* EndOF;

    /*!
     * \brief movingPointer a pointer created to move inside the register
     * This pointer allows the program to search without creating new variable althought this means it has to be reset constantly
     */
    void* movingPointer;

    /*!
     * \brief fullRegister the amount of full registers in the file
     * This space in the header allows the program to know how many used register are there
     */
    int* fullRegister;

    /*!
     * \brief freeRegister the amount of free registers in the file
     * This space in the header allows the program to know how many empty register are there, these are marked by setting "nullChar" as their first char
     */
    int* freeRegister;

    /*!
     * \brief registerSize the size of the full register
     * Since the size is constant this space is very useful to manage movingPointer and fonding the last register from the EndOf
     */
    int* registerSize;        //size of Register in bytes

    /*!
     * \brief addRegister modifies the header to show that a register has been added
     *
     * This function doesn't add a register to the file but rather keeps the rest of the program from touching the header.
     * It follows the logic of the rest of the program meaning that if there are free registers it will eliminate one and add a full register
     * if there are no free registers it will just add a new register
     */
    void addRegister();

    /*!
     * \brief removeRegister modifies the header to show that a register has been removed
     *
     * This function doesn't remove a register to the file but rather keeps the rest of the program from touching the header
     * It follows the logic of the rest of the program meaning that if there are free registers at the end of the program,
     * it will automatically erase them and move the EndOF to the end of the last full register
     * if there are no free registers before the one erassed it will simply remove the register
     */
    void removeRegister();

    /*!
     * \brief totalRegister adds the free and full registers
     * \return the quantity of registerSize
     * This function simply adds the value from the two pointers and adds them, ie, this value multiplied by the size of register plus the header size is the size of the file
     * It can also help to check if the amount of deleted registers in a compression equals the amount of free registers
     */
    int totalRegister();

    /*!
     * \brief resetmovingPointer makes the value of movingPointer equal to the beggining of the file
     */
    void resetmovingPointer();
};

#endif // HEADERMANAGER_H
