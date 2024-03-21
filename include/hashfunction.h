#ifndef HASHFUNCTION_H
#define HASHFUNCTION_H
#include <iostream>
#include <string>
#include <cmath>
#include <stockstruct.h>
#define hashtableSize 50

using namespace std;

class hashfunction
{
    public:
        hashfunction();
        int calcHash(string wkn);
        void sortHash(stock testStock, hashtable* newHashtable);

    private:
        int hashCode;
        int hashConstant;
};

#endif // HASHFUNCTION_H
