#ifndef REGISTERMANAGER_H
#define REGISTERMANAGER_H

class RegisterManager
{
public:
    RegisterManager();

    void RegisterManager::createTable(string tableName, SimpleList tableColumns, int<> columnsize, int regSize);

    void RegisterManager::select(string tableName, SimpleList tableColumns, SimpleList Conditions);

    void RegisterManager::insertInto(string tableName, SimpleList tableColumns, SimpleList values);

    void RegisterManager::update(string tableName, SimpleList tableColumns, SimpleList values, SimpleList conditions);

    void RegisterManager::deleteFrom(string tableName, SimpleList conditions);

    void RegisterManager::createIndexOn(string tableName, string column, string type);

    void RegisterManager::compressTable(string tableName);

    void RegisterManager::backupTable(string tableName);

    void RegisterManager::restoreTable(string tableName)
};

#endif // REGISTERMANAGER_H
SimpleList
