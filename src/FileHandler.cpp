#include "FileHandler.h"

FileHandler::FileHandler() : abort(false), name(" "){}

void FileHandler::getFilename(string parameter)
{
    //buffer to store characters for filename
    vector<char> buffer;
    string key = ".";
    //search for . in filepath
    int position = parameter.find(key);
    if (position != (int)string::npos)
    {
        //search from . to front of filepath until first \, everything between . and \ is the filename
        for(int i = position - 1; i >= 0 && parameter[i] != '\\'; i--)
        {
            buffer.push_back(parameter[i]);
        }
        string temp(buffer.begin(), buffer.end());
        name = temp;
        //name read in reverse, reverse again for correct name
        reverse(name.begin(), name.end());
        abort = false;
    }
    else
    {
        cout << "not a valid file path" << endl;
        abort = true;
    }
}

void FileHandler::import(string parameter)
{
    getFilename(parameter);

    if(abort)
    {
        abort = false;
        return;
    }

    //open file, check if file found
    ifstream iFile;
    iFile.open(parameter);
    if(!iFile.is_open())
    {
        cout << "file not found" << endl;
        return;
    }

    //push every line of csv file in stockLines
    vector<string> stockLines;
    int counter;
    while(!iFile.eof())
    {
        string temp;
        getline(iFile, temp);
        stockLines.push_back(temp);
        counter++;
    }

    //push every date of every line into private date vector
    //counter -- first to avoid first line of csv (not data but atribute names)
    for(int i = 0; i < (int)stockLines.size() - 1; i++)
    {
        string temp;
        counter--;
        istringstream data(stockLines[counter]);
        getline(data, temp, ',');
        stockDate.push_back(temp);
        //push all other data into two dimensional double vector
        //6 times for the rest of dataset values
        vector<double> row;
        for(int k = 0; k < 6; k++)
        {
            string temp;
            getline(data, temp, ',');
            float number = stod(temp);
            row.push_back(number);
        }
        stockData.push_back(row);
    }

    iFile.close();
}

//returns read data from csv as stock vector to sort in table later
vector<stock> FileHandler::convertToStock()
{
    vector<stock> tempVector;
    for(int i = 0; i < (int)stockDate.size(); i++)
    {
        stock tempStock;
        tempStock.name = name + to_string(i);
        tempStock.wkn = to_string(i);
        tempStock.shortCut = name;
        tempStock.date = stockDate[i];
        tempStock.open = stockDate[i][0];
        tempStock.high = stockDate[i][1];
        tempStock.low = stockDate[i][2];
        tempStock.close = stockDate[i][3];
        tempStock.volume = stockDate[i][4];
        tempStock.adjClose = stockDate[i][5];
        tempVector.push_back(tempStock);
    }

    return tempVector;
}

//saves table to file
void FileHandler::saveToFile(string parameter, hashtable newTable)
{
    ofstream oFile;
    //creates or opens .csv file with given name in files directory
    oFile.open("files/" + parameter + ".csv");
    //writes atribute names to file
    oFile << "Index,Name,WKN,shortCut,Date,Open,High,Low,Close,Adj Close,Volume\n";

    for(int i = 0; i < hashtableSize; i++)
    {
        hashnode* node = newTable.table[i];
        while(node != NULL)
        {
            //skips dummy node
            if(node->data.name == " ")
            {
                node = node->next;
                continue;
            }

            //writes data to file
            oFile << i
                  << "," << node->data.name
                  << "," << node->data.wkn
                  << "," << node->data.shortCut
                  << "," << node->data.date
                  << "," << node->data.open
                  << "," << node->data.high
                  << "," << node->data.low
                  << "," << node->data.close
                  << "," << node->data.adjClose
                  << "," << node->data.volume << "\n";

            node = node->next;
        }
    }
    oFile.close();
}

void FileHandler::loadFromFile(string parameter, hashtable* newTable)
{
    //checks for valid file path
    vector<char> buffer;
    string key = ".";
    int position = parameter.find(key);
    if (position == (int)string::npos)
    {
        cout << "not a valid file path" << endl;
        return;
    }

    //checks if file was opened
    ifstream iFile;
    iFile.open(parameter);
    if(!iFile.is_open())
    {
        cout << "file not found" << endl;
        return;
    }

    //deletes everything from table
    freeTable(newTable);

    //reads files from given file
    vector<string> stockLines;
    int counter;
    while(!iFile.eof())
    {
        string temp;
        getline(iFile, temp);
        stockLines.push_back(temp);
        counter++;
    }

    //writes data into table
    //fillTable(stockLines, newTable);

    iFile.close();
}

void FileHandler::freeTable(hashtable* newTable)
{
    for(int i = 0; i < hashtableSize; i++)
    {
        if(newTable->table[i] == NULL)
            continue;

        //starts at dummy node
        hashnode* node = newTable->table[i];

        //deletes everything from file
        while(node != NULL)
        {
            hashnode* tempNode = node;
            node = node->next;
            delete tempNode;
        }

        //places dummy note, which was deleted
        hashnode* newBegin = new hashnode;
        newBegin->next = NULL;

        newTable->table[i] = newBegin;
    }
}

void FileHandler::fillTable(vector<stock> stockLines, hashtable* newTable)
{

}
