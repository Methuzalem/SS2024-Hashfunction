#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include "stockstruct.h"

using namespace std;

class FileHandler
{
    public:
        FileHandler();
        void getFilename(string parameter);
        void import(string parameter);
        vector<stock> convertToStock();
        void saveToFile(string parameter, hashtable newTable);
        void loadFromFile(string parameter, hashtable* newTable);

    protected:

    private:
        bool abort;
        string name;
        vector<string> stockDate;
        vector<vector<double>> stockData;

        void freeTable(hashtable* newTable);
        void fillTable(vector<stock> stockLines, hashtable* newTable);
};

#endif // FILEHANDLER_H
