#include "writefile.h"

writefile::writefile()
{
}


void writefile::writeColumnNames(string* fileName, array<char*>* columnNames){
    string col = "Columns";
    string path = *fileName;
    path.append(col);
    array<char*> columnNames2Use = *columnNames;

    ofstream whatever(path.c_str() , ios::trunc);
    //cout << whatever.is_open() <<endl;
    for (int i = 0 ; i < columnNames2Use.getLenght() ; i++){
        whatever << columnNames2Use[i];
        if ( i < (columnNames->getLenght() - 1))
            whatever << "\n";
    }
    whatever.close();
}

//****************************************************************************//

/**
 * @brief createTable creates the database and metadata.
 * @param registerSize is the size for each registry.
 * @param columnSizes is the sizes for each column.
 */
bool writefile::createTable(int* registerSize, array<int>* columnSizes ,
                            array<char*>* columnNames , string* pFile){

    int offset = 0;
    string add;

    string theFileName = createNewFile(*pFile);
    writefile::writeColumnNames(&theFileName, columnNames);
    ofstream database (theFileName.c_str() , ios::trunc);

    //check if buffer = true
    if(database.is_open()){
        //cout << "****Database succesfully created***" << endl;
    }else{
        //cout << "****Database could not be created***" << endl;
        return false;
    }

    //Register size valideichion.
    if(*registerSize >= K->MAX_REGISTER_SIZE){
        cout << "Error: Register size beyond max size" << endl;
        return false;
    }else{
        database << K->TRIPLE_NULL;
        add = toChar(*registerSize);
        checkSize(&add, K->DEFAULT_REGISTER_SIZE);
        database.write(add.c_str() , K->DEFAULT_REGISTER_SIZE);
    }

    //set column sizes on file
    array<int> tempArr = *columnSizes;
    for (int i = 0 ; i < tempArr.getLenght() ; i++)
    {
        int integerElem = tempArr[i];
        add = toChar(integerElem);
        checkSize(&add,K->DEFAULT_COLUMN_SIZE);
        database.write(add.c_str() , K->DEFAULT_COLUMN_SIZE);
    }

    //sets seek on the end, gets the address then turns it to char
    //to insert on the beginning.
    database.seekp(offset, ios::end);
    int meta = database.tellp();
    string metadata = intToChar(meta);
    checkSize(&metadata, K->METADATA_SIZE);
    database.seekp(K->ZE_ROW);
    if (metadata.length() <= 3){
        const char *p = metadata.c_str();
        while (*p != '\0')
            database.put( *(p++) );
    }else{
        //cout << "Invalid metadata size. Yoh ! Pls kontact ur admin...\n";
        return false;
    }
    database.seekp(K->ZE_ROW , ios::end);
    database.close();
    return true;
}

/**
 * @brief writeRegister Method to append a whole registry. Add new element to database.
 * @param pFileName is the name of database file to add to.
 * @param pColumnData it's what to append.
 * @param columnPos is where to append it.
 */
bool writefile::writeRegister(string pFileName, array<char*>* pColumnData ,
                              array<char*>* pColumnNam){

    int currSeek = file.tellg();
    string standardDir = createNewFile(pFileName);
    file.open(standardDir.c_str());
    bool isOpen = true;

    if(!file.is_open()){
        cout << "NED "  + pFileName << endl;
        return false;
    }

    file.seekg(K->ZE_ROW);

    int spacesToMove;
    int Csize;
    int lon = pColumnNam->getLenght();

    array<char*> tempCDataArr = *pColumnData;
    array<char*> tempNames = *pColumnNam;
    array<int> ColumnPos (lon);

    string registerToWrite = K->EMPTY_STRING;
    string Cdata;

    const char* charT ;

    for (int i = K->ZE_ROW ; i < lon ; i++){
        charT  = tempNames[i];
        string strToAdd(charT);
        ColumnPos[i] = getColumnNumber(&pFileName, &strToAdd);
    }

    //Get the register and fill the blanks.
    fillString (&registerToWrite , getRegisterSize());

    for (int i = 0 ; i < ColumnPos.getLenght() ; i++){
        Cdata  = tempCDataArr[i];
        checkString(&Cdata);
        Csize = columnSize(ColumnPos[i]);
        //Not sure
        spacesToMove = sizeUntilColumn(ColumnPos[i]);
        fillString(&Cdata ,Csize);
        registerToWrite.replace(spacesToMove , Csize , Cdata.c_str());
    }

    if (file.is_open()){
        file.seekg(K->ZE_ROW , ios::end);
        file << registerToWrite;
    }
    file.seekg(currSeek);
    file.close();
    return isOpen;
}

/**
 * @brief updateField changes the value of a  given field on the whole database.
 * @param newData new information to be inserted.
 * @param pFile the database to be used
 * @param pRow
 * @param pColumn
 */
bool writefile::updateField(string newData, string pFile , int pRow , int pColumn){
    int currSeek = file.tellg();
    int sizeToColumn;
    int cSize;
    bool bowl = true;
    //Relative route + the name of the file
    if ( !(file.is_open()) ){
        string fileH = pFile;
        string standardDir = createNewFile(fileH.c_str());
        file.open(standardDir.c_str());
    }

    if ( !(file.is_open()) ){
        cout << "NED " + pFile << endl;
        bowl = false;
    }

    placeSeekOn(&pRow , &pColumn, &sizeToColumn, &cSize);
    fillString(&newData,cSize);


    if (file.is_open()){
        file << newData;
    }

    file.seekg(currSeek);

    if (file.is_open()){
        file.close();
    }
    return bowl;
}

/**
 * @brief updateColumn From pCname of pFile, replace pToCompare with newData
 * @param newData
 * @param pToCompare
 * @param pFile
 * @param pCName
 */
bool writefile::updateColumn(string newData,string pToCompare, string pFile, string pCName){

    int currSeek = file.tellg();
    int sizeToColumn;
    int cSize;
    string standardDir;
    bool bowl = true;

    //Relative route + the name of the file
    if ( !(file.is_open()) ){
        string fileH = pFile;
        standardDir = createNewFile(fileH.c_str());
        file.open(standardDir.c_str());
    }

    if ( !(file.is_open()) ){
        cout << "NED " + pFile << endl;
        bowl = false;
    }

    int Column = getColumnNumber(&standardDir , &pCName );
    int regQty = getRegisterQuantity();
    string currentData = K->EMPTY_STRING;

    for (int rowCounter = K->ONE_BYTE ; rowCounter <= regQty ; rowCounter++){

        //Move the seek to the column and register.
        placeSeekOn( &rowCounter , &Column, &sizeToColumn, &cSize);

        //Build the string of the old data
        for (int i = 0 ; i < cSize ; i++){
            char temp = file.get();
            if (temp == '*'){
                break;
            }else{
                currentData.push_back(temp);
            }
        }
        //Compare data.
        if (currentData == pToCompare){
            updateField(newData, pFile , rowCounter , Column);
        }else{
            currentData = K->EMPTY_STRING;
        }
    }

    file.seekg(currSeek);
    if (file.is_open()){
        file.close();
    }
    return bowl;
}

void writefile::backUpFile(string fileTobackUp){
    string backUp= "backup";
    backUp.append(fileTobackUp); //backupTest8

    string pathFileToBackUp = createNewFile(fileTobackUp); //../FSQL/Test8
    string pathbackUpFile = createNewBackUp(backUp);// ../FSQL/backupTest8

    ofstream newfile (pathbackUpFile.c_str() , ios::trunc);
    newfile.close();

    std::ifstream ifs(pathFileToBackUp.c_str(), std::ios::binary);
    std::ofstream ofs(pathbackUpFile.c_str(), std::ios::binary);

    ofs << ifs.rdbuf();

    ifs.close();
    ofs.close();

    pathFileToBackUp.append("Columns");
    pathbackUpFile.append("Columns");

    ofstream newfile2 (pathbackUpFile.c_str() , ios::trunc);
    newfile2.close();

    std::ifstream ifs2(pathFileToBackUp.c_str(), std::ios::binary);
    std::ofstream ofs2(pathbackUpFile.c_str(), std::ios::binary);

    ofs2 << ifs2.rdbuf();

    ifs2.close();
    ofs2.close();
}

/**
 * @brief writefile::restoreFile
 * @param fileToRestore
 */
void writefile::restoreFile(string fileToRestore){
    string backUp= "backup";
    backUp.append(fileToRestore);

    string pathFileToRestore = createNewBackUp(backUp);
    string pathRestoredFile = createNewFile(fileToRestore);

    ofstream newfile (pathRestoredFile.c_str() , ios::trunc);
    newfile.close();


    std::ifstream ifs(pathFileToRestore.c_str(), std::ios::binary);
    std::ofstream ofs(pathRestoredFile.c_str(), std::ios::binary);

    ofs << ifs.rdbuf();

    ifs.close();
    ofs.close();

    pathFileToRestore.append("Columns");
    pathRestoredFile.append("Columns");

    ofstream newfile2 (pathRestoredFile.c_str() , ios::trunc);
    newfile2.close();

    std::ifstream ifs2(pathFileToRestore.c_str(), std::ios::binary);
    std::ofstream ofs2(pathRestoredFile.c_str(), std::ios::binary);

    ofs2 << ifs2.rdbuf();

    ifs2.close();
    ofs2.close();
}

bool writefile::deleteRegister(string pFile, string pCName, string newData){
    int currSeek = file.tellg();
    int Column;
    int cSize;
    string standardDir;
    bool bowl = true;

    //Relative route + the name of the file
    if ( !(file.is_open()) ){
        standardDir = createNewFile(pFile.c_str());
        file.open(standardDir.c_str());
    }

    if ( !(file.is_open()) ){
        cout << "NED " + pFile << endl;
        return false;
    }

    Column = getColumnNumber(&standardDir , &pCName );
    cSize = getRegisterSize();
    int regQty = getRegisterQuantity();
    string voidField = K->EMPTY_STRING;
    int sizeToColumn = sizeUntilColumn(Column);

    fillString(&voidField,cSize);
    cout << voidField.length() <<endl;
    for (int rowCounter = K->ONE_BYTE ; rowCounter <= regQty ; rowCounter++){

        //Compare data.
        if (readField(pFile , rowCounter , Column) == newData){
            placeSeekOn(&rowCounter , &Column, &sizeToColumn, &cSize);
            if (file.is_open()){
                file << voidField;
            } else {
                bowl = false;
            }
        }
    }

    file.seekg(currSeek);
    if (file.is_open()){
        file.close();
    }
    return bowl;
}
