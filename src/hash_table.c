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


int initialiseHashTable(ht_hash_table* hashTable, int size)
{
    hashTable->size = size;
    hashTable->count = 0;
    // hashTable->items = calloc((size_t)hashTable->size, sizeof(hashTable->items));
    hashTable->items = malloc(hashTable->size * sizeof(hashTable->items));
    return 1;
}

int insert(ht_hash_table* hashTable, char* key, void* value)
{
    int hashVal = hash(key, hashTable->size);
    int baseIndex;
    int currIndex;

    if(isFull(hashTable))
    {
        // printf("[Error] The hashtable is full. It is meant to extend, but not yet!\n");
        printf("[Info] The hashtable is full. Resizing the hashtable.\n");
        resize(hashTable);
        insert(hashTable, key, value);
        return 1;
    }
    
    if(hashTable->items[hashVal] == NULL)
    {
        ht_item* tempItem = malloc(sizeof(tempItem));
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
                ht_item* tempItem = malloc(sizeof(tempItem));
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


int delete(ht_hash_table* hashTable, char* key)
{
    int hashVal = hash(key, hashTable->size);
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
        ht_item* tempItem = malloc(sizeof(tempItem));
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
                ht_item* tempItem = malloc(sizeof(tempItem));
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

int update(ht_hash_table* hashTable, char* key, char* value)
{   
    int retIndex = getIndex(hashTable, key);

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

char* search(ht_hash_table* hashTable, char* key)
{   
    int retIndex = getIndex(hashTable, key);

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

int getIndex(ht_hash_table* hashTable, char* key)
{
    int hashVal = hash(key, hashTable->size);
    int length = hashTable->size;

    if(strcmp(key, hashTable->items[hashVal]->key) == 0)
    {
        return hashVal;
    }
    else
    {
        for(int i=hashVal+1; i<length; i++)
        {   if(hashTable->items[i] != NULL)
            {
                if(strcmp(key, hashTable->items[i]->key) == 0)
                {
                    return i;
                }    
            }
        }
        printf("[Error] Can't find the bucket with key %s\n",key);
        return -1;
    }
}

int resize(ht_hash_table* hashTable)
{
    int sizeNew = generatePrime((hashTable->size));
    printf("[Info]================Resizing================\n");
    printf("[Info] Resized to %d\n",sizeNew);

    ht_hash_table* hashTableNew = malloc(sizeof(*hashTableNew));

    initialiseHashTable(hashTableNew, sizeNew);

    for(int i=0;i<hashTable->count;i++)
    {
        insert(hashTableNew, hashTable->items[i]->key, hashTable->items[i]->value);
    }


    *hashTable = *hashTableNew;
    free(hashTableNew);

    return 1;
}


int hash(char* key, int htLength)
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
    hash = hash % htLength;
    // printf("%d\n", hash);
    return hash;
}


int isFull(ht_hash_table* hashTable)
{
    if(hashTable->size == hashTable->count)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
