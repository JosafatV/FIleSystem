#ifndef DECRIPTOR_H
#define DECRIPTOR_H

class Decriptor
{
public:
    Decriptor();

//    string tableName;
//    SimpleList values = new SimpleList();
//    SimpleList columns = new SimpleList();
//    SimpleList conditions = new SimpleList();
//    SimpleList booperands = new SimpleList();

    void interpreter (string Line, int id);

private:

    string getName (string description);

    string getColumns(bool simpleCol, string description);

    string getValues(string description);

    string getExpression (string temp);

    string getConditions(string description);



};

#endif // DECRIPTOR_H
