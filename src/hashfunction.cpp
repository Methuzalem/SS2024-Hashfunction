#include "hashfunction.h"
#include <string>

hashfunction::hashfunction()
{
    hashCode = 0;
    hashConstant = 31;
}

int hashfunction::calcHash(string wkn)
{
    //calculates hashcode for sorting
    int length = wkn.length();

    for(int i = 0; i < length; i++)
    {
        hashCode += (int)wkn[i] * pow(hashConstant, length - i - 1);
    }

    return hashCode%hashtableSize;
}

void hashfunction::sortHash(stock testStock, hashtable* newHashtable)
{
    //calculates hash for sorting
    int index = calcHash(testStock.wkn);

    //creates new node to be put at end of list
    hashnode* newNode = new hashnode;
    newNode->data = testStock;
    newNode->next = NULL;

    //creates dummy node
    hashnode* newBegin = new hashnode;
    newBegin->next = newNode;

    //if there is no dummy node, place dummy node
    if(newHashtable->table[index] == NULL)
    {
        newHashtable->table[index] = newBegin;
        newBegin->next = newNode;
    }
    else
    {
        //go to end of list and place stock node
        hashnode* current = newHashtable->table[index];
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}
