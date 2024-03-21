#include <iostream>
#include "FileHandler.h"
#include "InputHandler.h"
#include "hashfunction.h"
#include "search.h"
#include "stockstruct.h"

int main()
{
    //inputhandler takes user input and calls functions of other classes as needed
    InputHandler input;
    //filehandler can import a csv file an write data into a hash table
    //can also save table to a csv file and load from such file
    FileHandler  reader;
    //hashfunction calculates the required hashkey with the wkn of a stock and sorts the stock into the table
    hashfunction myHash;
    //searcher can find a stock in a table by wkn
    //it then prints that stock with the search function
    //or deletes that stock with the delete function
    searchstock  searcher;
    //table data sctucture defined in stockstruct.h
    //stockstruct.h also defines stock structure
    hashtable    newTable;

    //main loop, take input handles all program logic
    while(1)
    {
        if(input.takeInput(reader, myHash, searcher, &newTable))
        {
            break;
        }
    }

    return 0;
}
