/**
 * @file hash_table.c
 * @author Danny Khuu
 * @brief C file for the open addressing hash table data structure and functions
 * @version 0.1
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "hash_table.h"


int initialise_ht(HashTable* hashTable, int size)
{
    size = (size <= 0) ? DEFAULT_INITIAL_CAPACITY : initSize_ht(size);

    hashTable->size = size;
    hashTable->count = 0;
    // hashTable->items = calloc((size_t)hashTable->size, sizeof(hashTable->items));
    hashTable->items = malloc(hashTable->size * sizeof(hashTable->items));
    return 1;
}

int insert_ht(HashTable* hashTable, char* key, void* value)
{
    int hashVal = hash_ht(key, hashTable->size);
    int baseIndex;
    int currIndex;

    if(isFull_ht(hashTable))
    {
        // printf("[Error] The hashtable is full. It is meant to extend, but not yet!\n");
        printf("[Info] The hashtable is full. Resizing the hashtable.\n");
        resize_ht(hashTable);
        insert_ht(hashTable, key, value);
        return 1;
    }
    
    if(hashTable->items[hashVal] == NULL)
    {
        HashTableItem* tempItem = malloc(sizeof(tempItem));
        tempItem->key = strdup(key);
        tempItem->value = strdup(value);
        hashTable->items[hashVal] = tempItem;
        hashTable->count ++;
        printf("[Info] Inserted key \"%s\" value \"%s\" index %d\n", key, (char*)value, hashVal);
        return 1;
    }
    else
    {   
        printf("[Info] Collision for index %d for key %s\n", hashVal, key);
        baseIndex = hashVal;
        for(int i=0;i<hashTable->size;i++)
        {
            currIndex = baseIndex + i;
            if(currIndex == hashTable->size)
            {
                printf("[Info] Reset the hash table index for empty buckets\n");
                baseIndex = 0;
                i = -1;
            }
            else if(hashTable->items[currIndex] == NULL)
            {
                HashTableItem* tempItem = malloc(sizeof(tempItem));
                tempItem->key = strdup(key);
                tempItem->value = strdup(value);
                hashTable->items[currIndex] = tempItem;
                hashTable->count ++;
                printf("[Info] Inserted key \"%s\" with value \"%s\" at index %d\n", key, (char*)value, currIndex);
                return 1;
            }
        }
        printf("[Error] The item was not insertable even though it has space.\n");
        printf("[Error] Key %s value %s", key, ((char *)value));
        return 0;
    }
}


int delete_ht(HashTable* hashTable, char* key)
{
    int hashVal = hash_ht(key, hashTable->size);
    int baseIndex;
    int currIndex;
    char* tempVal;

    if(hashTable->items[hashVal] == NULL)
    {
        printf("[Error] Invalid key \"%s\". Cannot search.\n",key);
        return 0;
    }

    if(strcmp(hashTable->items[hashVal]->key, key) == 0)
    {
        HashTableItem* tempItem = malloc(sizeof(tempItem));
        tempVal = hashTable->items[hashVal]->value;
        hashTable->items[hashVal] = tempItem;
        hashTable->count --;
        printf("[Info] Deleted item with key: %s value: %s\n", key, tempVal);
        return 1;
    }
    else
    {
        baseIndex = hashVal;
        for(int i=0;i<hashTable->size;i++)
        {
            currIndex = baseIndex + i;
            // printf("current index %d\n", currIndex);
            if(currIndex == hashTable->size)
            {
                baseIndex = 0;
                i = -1;
            }
            else if(strcmp(hashTable->items[currIndex]->key, key) == 0)
            {
                HashTableItem* tempItem = malloc(sizeof(tempItem));
                tempVal = hashTable->items[currIndex]->value;
                hashTable->items[currIndex] = tempItem;
                hashTable->count --;
                printf("[Info] Deleted item with key: %s value: %s\n", key, tempVal);
                return 1;
            }
        }
        printf("[Warning] Could not delete the key %s, it does not seem to exist.\n",key);
        return 0;
    }
}

int update_ht(HashTable* hashTable, char* key, char* value)
{   
    int retIndex = getIndex_ht(hashTable, key);

    if(retIndex != -1)
    {
        printf("[Info] Found bucket for key %s\n",key);
        hashTable->items[retIndex]->value = strdup(value);
        return 1;
    }
    else
    {
        printf("[Error] Can't find the bucket with key %s\n",key);
        return 0;
    }
}

char* search_ht(HashTable* hashTable, char* key)
{   
    int retIndex = getIndex_ht(hashTable, key);

    if(retIndex != -1)
    {
        return hashTable->items[retIndex]->value;
    }
    else
    {
        printf("[Error] Can't find the bucket with key %s\n",key);
        return NULL;
    }
}

int getIndex_ht(HashTable* hashTable, char* key)
{
    int hashVal = hash_ht(key, hashTable->size);
    int length = hashTable->size;

    if(strcmp(key, hashTable->items[hashVal]->key) == 0)
    {
        return hashVal;
    }
    else
    {
        for(int i=hashVal+1; i<length; i++)
        {   if((hashTable->items[i] != NULL) && (strcmp(key, hashTable->items[i]->key) == 0))
            {
                return i;
            }
        }
        printf("[Error] Can't find the bucket with key %s\n",key);
        return -1;
    }
}

int resize_ht(HashTable* hashTable)
{
    int sizeNew = generatePrime((hashTable->size));
    printf("[Info]================Resizing================\n");
    printf("[Info] Resized to %d\n",sizeNew);

    HashTable* hashTableNew = malloc(sizeof(*hashTableNew));

    initialise_ht(hashTableNew, sizeNew);

    for(int i=0;i<hashTable->count;i++)
    {
        insert_ht(hashTableNew, hashTable->items[i]->key, hashTable->items[i]->value);
    }


    *hashTable = *hashTableNew;
    free(hashTableNew);

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

int isFull_ht(HashTable* hashTable)
{
    return (hashTable->size == hashTable->count) ? 1 : 0;
}
