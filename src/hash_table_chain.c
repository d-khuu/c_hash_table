/**
 * @file hash_table.c
 * @author Danny Khuu
 * @brief C file for the separate chaining hash table data structure 
 *        and functions 
 * @version 0.1
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "hash_table_chain.h"


int initialise_ht(HashTable* hashTable, int size)
{
    size = (size <= 0) ? DEFAULT_INITIAL_CAPACITY : initSize_ht(size);

    hashTable->size = size;
    hashTable->count = 0;
    // hashTable->items = calloc((size_t)hashTable->size, sizeof(hashTable->items));
    hashTable->items = malloc(hashTable->size * sizeof(hashTable->items));
    for(int i = 0;i<size;i++)
    {
        LinkedList * linkedList = malloc(sizeof(*linkedList));
        initialise_ll(linkedList);
        hashTable->items[i] = linkedList;
    }
    return 1;
}

int insert_ht(HashTable* hashTable, char* key, void* value)
{
    int hashVal = hash_ht(key, hashTable->size);
    int errorCode;

    if(isFull_ht(hashTable, hashVal))
    {
        printf("[Info] The hashtable is full. Resizing the hashtable.\n");
        resize_ht(hashTable);
        insert_ht(hashTable, key, value);
        return 1;
    }
    
    errorCode = insert_ll(hashTable->items[hashVal], key, value);
    if(errorCode == 1)
    {
        printf("[Info] Inserted key \"%s\" value \"%s\" index %d\n", key, (char*)value, hashVal);
        return 1;
    }
    else
    {
        return 0;
    }
}


int delete_ht(HashTable* hashTable, char* key)
{
    int hashVal = hash_ht(key, hashTable->size);
    int errorCode;

    if(hashTable->items[hashVal] == NULL)
    {
        printf("[Error] Invalid key \"%s\". Cannot search.\n",key);
        return 0;
    }

    errorCode = delete_ll(hashTable->items[hashVal], key);
    return errorCode;
}

int update_ht(HashTable* hashTable, char* key, char* value)
{   
    int hashVal = hash_ht(key, hashTable->size);
    int errorCode = update_ll(hashTable->items[hashVal], key, value);
    return errorCode;
}

char* search_ht(HashTable* hashTable, char* key)
{   
    int hashVal = hash_ht(key, hashTable->size);
    char* retStr = search_ll(hashTable->items[hashVal], key);
    return retStr;
}

int resize_ht(HashTable* hashTable)
{
    int sizeNew = generatePrime((hashTable->size));
    printf("[Info]================Resizing================\n");
    printf("[Info] Resized to %d\n",sizeNew);

    HashTable* hashTableNew = malloc(sizeof(*hashTableNew));

    initialise_ht(hashTableNew, sizeNew);
    // printf("[Debugging] hashmap size is %d\n", hashTable->size);
    for(int i=0;i<hashTable->size;i++)
    {
        Node* currNode = hashTable->items[i]->head;
        if(hashTable->items[i]->head == NULL)
        {
            // printf("[Debug] Linkedlist at index %d is null.\n", i);
            continue;
        }
        do
        {
            // printf("[Debug] Attempting to insert key %s value %s\n", currNode->key, currNode->value);
            insert_ht(hashTableNew, currNode->key, currNode->value);
            currNode = currNode->next;
        } while (currNode != NULL);
    }

    *hashTable = *hashTableNew;
    free(hashTableNew);
    printf("[Info]===========Complete Resizing============\n");

    return 1;
}


int hash_ht(char* key, int htLength)
{
    int hash = -1;
    int keyLength = strlen(key);

    for(int i=0;i<keyLength;i++)
    {
        hash = (hash == -1) ? key[i] : (hash + key[i]);
    }
    hash = hash % htLength;
    return hash;
}

int initSize_ht(int size)
{
    int exitCode = isPrime(size);
    if(exitCode == 1)
    {
        printf("[Info] The value %d is a prime number.\n", size);
    }
    else
    {
        printf("[Warning] The value %d is not a prime number.\n", size);
        size = generatePrime(size);
        printf("[Warning] We'll generate one for you. Here, it will be %d.\n", size);
    }
    return size;
}

int isFull_ht(HashTable* hashTable, int hashValue)
{
    return ((hashTable->items[hashValue]->size + 1) > ((int)(hashTable->size*LOAD_FACTOR))) ? 1 : 0;
}