#ifndef DECRIPTOR_H
#define DECRIPTOR_H

class Decriptor
{
public:
    Decriptor();

    /*!
     * \brief tableName - the name by which the file will be recognized
     */
    //string tableName;

    /*!
     * \brief values - the values that the register will have when created
     */
    //SimpleList values = new SimpleList();

    /*!
     * \brief columns - the name of the columns, in order, that compose the file
     */
    //SimpleList columns = new SimpleList();

    /*!
     * \brief conditions - a special list that holds the value of the comparator and the value to which the entry will be compared to
     */
    //SimpleList conditions = new SimpleList();

    /*!
     * \brief booperands - a list with the boolean operands for the comparison
     */
    //SimpleList booperands = new SimpleList(string);

    /*!
     * \brief interpreter - parses the string that the user inputed according to the first command
     * \param Line - the string written by the user
     * \param id - the id for Lines with the same command but different processing
     *
     * Since the commands inputed are not easily parsed by an individual code they are splitted according to it's mayor blocks to parse them into something useful
     * This function only takes correct strings, the blocks become SimpleLists of various kinds for the program to use
     */
    void interpreter (string Line, int id);

private:

    /*!
     * \brief emptyVariables sets all variable empty
     *
     * Given that these variables are used once to complete a command and are based on the .append method,
     * everytime you start a command you need these variables empty, so at the end of every command completion this method cleans them.
     */
    void emptyVariables();

    /*!
     * \brief getName - gets the name of the table
     * \param description - the description after the command
     * \return the new description without the parsed info
     */
    string getName (string description);

    //parse the columns to integers (indexes) immediately, create a nullIndex for empty columns
    //parse values to another SimpleList -> more RAM vs more speed
    /*!
     * \brief getColumns - gets the columns to be affected by the command
     * \param simpleCol - the type of column extraction to be made
     * \param description - the description after the command
     * \return the new description without the parsed info
     *
     * This function takes a string from '(' to ')' and get the user inputed value and the operand,
     * the first condition is ignored since is easier for the program to check all values given the properties of the conditions (they can compare outside the given columns)
     * this is made this way knowing that it may cause an error if the same value is in two columns of the same register.
     * This function takes an extra argument due to the different kinds of column arrangement (with an without values)
     */
    string getColumns(bool simpleCol, string description);

    /*!
     * \brief getValues - gets the values to be computed in the register
     * \param description - the description after the command
     * \return the new description without the parsed info
     *
     * uses the same logic as the simpleCol algorythm in getColumns, cuts in ',' and adds the strings in the middle to a SimpleList
     */
    string getValues(string description);

    /*!
     * \brief getExpression - gets the operand/value SimpleList to compare values
     * \param temp - a piece of the description that contains compare/operator/value
     * \return the modified temp without the parsed info
     */
    string getExpression (string temp);

    /*!
     * \brief getConditions - gets the operand/value SimpleList to compare values and the booperands for boolean comparisons (and/or)
     * \param description - the description after the command
     * \return the new description without the parsed info
     *
     * since the boolean operators require two comparisons in each side this functtion was splitted, getExpression manages the comparisons at the sides and getConditions the boolean comparisons
     */
    string getConditions(string description);

};

#endif // DECRIPTOR_H
