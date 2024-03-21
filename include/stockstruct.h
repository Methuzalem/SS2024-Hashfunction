#ifndef STOCKSTRUCT_H
#define STOCKSTRUCT_H
#include <iostream>
#include <string>
#define hashtableSize 50

using namespace std;

typedef struct stock
{
    string name;
    string wkn;
    string shortCut;
    string date;
    double open;
    double high;
    double low;
    double close;
    double volume;
    double adjClose;

    stock()
    {
        name = " ";
        wkn = " ";
        shortCut = " ";
        date = " ";
        open = 0.0;
        high = 0.0;
        low = 0.0;
        close = 0.0;
        volume = 0.0;
        adjClose = 0.0;
    }

} stock;

typedef struct hashnode
{
    stock data;
    struct hashnode* next;
} hashnode;

typedef struct hashtable
{
    hashnode* table[50];

    hashtable()
    {
        for(int i = 0; i < hashtableSize; i++){
            table[i] = NULL;
        }
    }

} hashtable;

#endif // STOCKSTRUCT_H
