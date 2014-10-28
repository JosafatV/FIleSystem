#ifndef REGISTER_H
#define REGISTER_H

class Register
{
public:
    Register();

    string Filename;
    SimpleList ColumnName = new SimpleList ();
    SimpleList ColumnSize = new SimpleList ();
    char nullChar = '/o';

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
     * \brief ColumnNametoColumnSize converts the name of a column to the index of it's respective matrix
     * \param Name name of the column
     * \return the index (int)
     */
    int ColumnNametoColumnSize (string Name);
};

#endif // REGISTER_H
