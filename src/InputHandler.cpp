#include "InputHandler.h"

InputHandler::InputHandler() {}

int InputHandler::takeInput(FileHandler reader, hashfunction myHash, searchstock searcher, hashtable* newTable)
{
    //print possible commands for user
    cout << "ADD    <name, wkn, shortcut>: stock with name, wkn, shortcut to table" << endl;
    cout << "DEL    <wkn>     : delete stock from table" << endl;
    cout << "IMPORT <filepath>: import stocks from csv file" << endl;
    cout << "PLOT             : prints hashtree" << endl;
    cout << "SEARCH <wkn>     : search for specific stock with wkn" << endl;
    cout << "SAVE   <filename>: save table to file" << endl;
    cout << "LOAD   <path>    : loads table from file" << endl;
    cout << "QUIT: ends programm" << endl;

    //take input
    string input;
    getline(cin, input);
    string command;
    vector<string> parameter;
    stringstream tempInput(input);
    string tempParameter;

    //extrace chosen command from input
    getline(tempInput, command, ' ');
    while(!tempInput.eof())
    {
        //extract all arguments for that command
        getline(tempInput, tempParameter, ' ');
        parameter.push_back(tempParameter);
    }

    //if else sequence for chosen command
    //commands that require additional arguments ask for number of arguments before proceeding
    if(command == "ADD")
    {
        if(parameter.size() < 3)
        {
            cout << "not enough arguments" << endl;
            return 0;
        }
        //addStock returns a stock from arguments extraced from input
        //sortHash sorts that stock into the hash table newTable
        myHash.sortHash(addStock(parameter), newTable);
    }
    else if(command == "DEL")
    {
        if(parameter.size() < 1)
        {
            cout << "not enough arguments" << endl;
            return 0;
        }
        //deleteByWKN finds stock in table by argument 0, hashes it with myHash object and sorts
        searcher.deleteByWKN(parameter[0], myHash, *newTable);
    }
    else if(command == "IMPORT")
    {
        if(parameter.size() < 1)
        {
            cout << "not enough arguments" << endl;
            return 0;
        }
        //reader stores results of file in private vectors
        reader.import(parameter[0]);
        //sonverToStock returns stock vector from private vectors
        vector<stock> temp = reader.convertToStock();
        //sorts each hash in stock vector into table
        for(int i = 0; i < (int)temp.size(); i++)
            myHash.sortHash(temp[i], newTable);
    }
    else if(command == "PLOT")
    {
        //prints table
        printTable(*newTable);
    }
    else if(command == "SEARCH")
    {
        if(parameter.size() < 1)
        {
            cout << "not enough arguments" << endl;
            return 0;
        }
        //finds stock by wkn and prints to console
        searcher.searchByWKN(parameter[0], myHash, *newTable);
    }
    else if(command == "SAVE")
    {
        if(parameter.size() < 1)
        {
            cout << "not enough arguments" << endl;
            return 0;
        }
        //saves table to file
        reader.saveToFile(parameter[0], *newTable);
    }
    else if(command == "LOAD")
    {
        if(parameter.size() < 1)
        {
            cout << "not enough arguments" << endl;
            return 0;
        }
        //loads table from file
        reader.loadFromFile(parameter[0], newTable);
    }
    else if(command == "QUIT")
    {
        return 1;
    }

    return 0;
}

stock InputHandler::addStock(vector<string> parameter)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stock temp;
    temp.name = parameter[0];
    temp.wkn = parameter[1];
    temp.shortCut = parameter[2];
    temp.date = to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday);
    return temp;
}

void InputHandler::printTable(hashtable table)
{
    cout << "Hashtable Inhalt:" << endl;
    for(int i = 0; i < hashtableSize; i++) {
        cout << "Index " << i << ": ";
        hashnode* node = table.table[i];
        //print empty if list only has dummy node or is empty
        if (node == NULL || (node->data.name == " " && node->next == NULL)) {
            cout << "empty" << endl;
        } else {
            //print name, wkn and date of all stocks in table
            node = node->next;
            while (node != NULL) {
                cout << "Stock Name: " << node->data.name << ", WKN: " << node->data.wkn << ", Date: " << node->data.date << ";";
                node = node->next;
            }
            cout << endl;
        }
    }
}
