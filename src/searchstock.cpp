#include "searchstock.h"

searchstock::searchstock() {}

void searchstock::searchByWKN(string wkn, hashfunction myHash, hashtable hashT)
{
    //calcs hashcode for searching, creates temporary node for going through list
    int index = myHash.calcHash(wkn);
    hashnode* node = hashT.table[index];

    while(node != NULL)
    {
        //when stock is found, print, then return
        if (node->data.wkn == wkn)
        {
            cout << "Stock gefunden!" << endl;
            cout << "Name: " << node->data.name << endl;
            cout << "WKN: " << node->data.wkn << endl;
            cout << "ShortCut: " << node->data.shortCut << endl;
            cout << "Date: " << node->data.date << endl;
            cout << "Open: " << node->data.open << endl;
            cout << "High: " << node->data.high << endl;
            cout << "Low: " << node->data.low << endl;
            cout << "Close: " << node->data.close << endl;
            cout << "Adj Close: " << node->data.adjClose << endl;
            cout << "Volume: " << node->data.volume << endl;
            return;
        }
        node = node->next;
    }
    std::cout << "Kein Eintrag fuer WKN " << wkn << " gefunden." << std::endl;
}

void searchstock::deleteByWKN(string wkn, hashfunction myHash, hashtable hashT)
{
    //calcs hashcode for searching, creates temporary node for going through list
    int index = myHash.calcHash(wkn);
    hashnode* node = hashT.table[index];

    //if stock is at beginning of list, delete and set head at next element
    if(node->data.wkn == wkn){
        hashnode* newbegin = NULL;
        node->next = newbegin;
        free(node);
        return;
    }

    //else go through list until stock is found, delete, connect node before to node after
    while(node->next != NULL){
        if(node->next->data.wkn == wkn){
            hashnode* temp = node->next;
            node->next = node->next->next;
            free(temp);
            break;
        }
        node = node->next;
    }
    std::cout << "Eintrag mit WKN: " << wkn << " geloescht." << std::endl;
}
