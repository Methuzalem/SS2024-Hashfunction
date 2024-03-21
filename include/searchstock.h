#ifndef SEARCHSTOCK_H
#define SEARCHSTOCK_H
#include <string>
#include <iostream>
#include "stockstruct.h"
#include "hashfunction.h"

using namespace std;

class searchstock
{
    public:
        searchstock();
        void searchByWKN(string wkn, hashfunction myHash, hashtable hashT);
        void deleteByWKN(string wkn, hashfunction myHash, hashtable hashT);

    private:
};

#endif // SEARCHSTOCK_H
