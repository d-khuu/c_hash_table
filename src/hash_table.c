/**
 * @file hash_table.c
 * @author Danny Khuu
 * @brief 
 * @version 0.1
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "hash_table.h"

/**
 * @brief Static stuff
 * 
 */
static jmp_buf s_jumpBuffer;

int initialiseHashTable(ht_hash_table* hashTable, int size)
{
    if(setjmp(s_jumpBuffer))
    {
        hashTable->size = size;
        hashTable->count = 0;    
        return 0;
    }
    else
    {
        throw();
        return 2;
    }
}

int insert(ht_hash_table* hashTable, char* key, void* value)
{
    return 0;
}


int delete(ht_hash_table* hashTable, char* key)
{
    return 0;
}

int search(ht_hash_table* hashTable, char* key)
{
    int hashVal = hash(key);
    int length = hashTable->size;

    if(strcpy(hashTable->items[hashVal]->key, key))
    {
        return hashVal;
    }
    else
    {
        for(int i=hashVal+1; i<length; i++)
        {

        }
        return -1;
    }
}

int hash(char* key)
{
    int hash = -1;
    int keyLength = strlen(key);

    for(int i=0;i<keyLength;i++)
    {
        if(hash == -1)
        {
            hash = key[i];
        }
        else
        {
            hash += key[i];
        }
        //  printf("Char: %c -> Value: %d\n", key[i], key[i]);
    }

    return hash;
}


void throw()
{
    longjmp(s_jumpBuffer, 2);
}

