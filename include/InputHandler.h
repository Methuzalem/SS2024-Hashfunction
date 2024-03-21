#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include "FileHandler.h"
#include "hashfunction.h"
#include "searchstock.h"
#include "stockstruct.h"
#include <iostream>
#include <sstream>
#include <ctime>

class InputHandler
{
    public:
        InputHandler();
        int takeInput(FileHandler reader, hashfunction myHash, searchstock searcher, hashtable* newTable);
        stock addStock(vector<string> parameter);
        void printTable(hashtable newTable);

    protected:

    private:
};

#endif // INPUTHANDLER_H
