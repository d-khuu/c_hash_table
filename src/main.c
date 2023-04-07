/**
 * @file main.c
 * @author Danny Khuu
 * @brief 
 * @version 0.1
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "hash_table.h"
#define FILE_NAME "data.csv"

/**
 * @brief Loads the data from the csv file into the hashtable
 * 
 * @param hashTable 
 * @return int 
 */
int loadFromFile(ht_hash_table* hashTable)
{
    FILE * fptr;
    char str[100];
    char * keyTemp;
    char * valueTemp;
    fptr = fopen(FILE_NAME, "r");

    if(fptr == NULL)
    {
        printf("Unable to fine file with name %s\n",FILE_NAME);
        printf("Exiting\n");
        exit(EXIT_FAILURE);
    }

    while(feof(fptr) != 1)
    {
        fgets(str, 100, fptr);
        // printf("%s", str);

        keyTemp = strtok(str, ",\n");
        valueTemp = strtok(NULL, ",\n");
        // printf("key: %s value: %s\n",keyTemp, valueTemp);
        insert(hashTable, keyTemp, valueTemp);
        // if(isFull(hashTable))
        // {
        //     printf("[Warning] The hashtable is full\n");
        //     // break;
        // }
    }
    // printf("[Info] hashmap index: %s, value: %s\n", "town", search(hashTable, "town"));
    // printf("hashmap index: %s, value: %s\n", hashTable->items[1]->key, hashTable->items[1]->value);
    // printf("[Info] hashmap index: %s, value: %s\n", keyTemp, search(hashTable, keyTemp));
    printf("[Info] Complete import\n");
    fclose(fptr);
    // exit(0);
    return 1;
}

/**
 * @brief The main function just for testing the hash table
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("[Error] Size not provided.\n");
        exit(EXIT_FAILURE);
    }
    else if(atoi(argv[1]) == 0)
    {
        printf("[Error] Invalid integer %s.\n",argv[1]);
        exit(EXIT_FAILURE);
    }

    
    int SIZE_G = atoi(argv[1]);
    int exitCode;

    exitCode = isPrime(SIZE_G);
    if(exitCode == 1)
    {
        printf("[Info] The value %d is a prime number.\n", SIZE_G);
    }
    else
    {
        printf("[Warning] The value %d is not a prime number.\n", SIZE_G);
        SIZE_G = generatePrime(SIZE_G);
        printf("[Warning] We'll generate one for you. Here, it will be %d.\n", SIZE_G);
    }
    
    ht_hash_table* hashTablePtr = malloc(sizeof(*hashTablePtr));

    if(initialiseHashTable(hashTablePtr, SIZE_G) != 1)
    {
        printf("[Error] Failed to initialise the hash table.\n");
    }
    printf("[Info] Hash Table Size: %d, Count: %d.\n", hashTablePtr->size, hashTablePtr->count);
    
    loadFromFile(hashTablePtr);

    // char * keyTest = "sam";
    // void * valTest = "valueTest";
    // printf("%s\n",keyTest);

    // char * toon = "toonj";
    // void * val = "kingdom";
    // printf("hash of new is %d\n", hash(toon, hashTablePtr->size));
    
    // insert(hashTablePtr, keyTest, valTest);
    // insert(hashTablePtr, toon, val);
    // keyTest = (char *)malloc(20);
    // strcpy(keyTest, "fake");
    // printf("%s\n",keyTest);
    // printf("%d\n",hash(keyTest, hashTablePtr->size));
    // printf("key => %s = %d, item => %s\n", keyTest, hash(keyTest, hashTablePtr->size), hashTablePtr->items[hash(keyTest, hashTablePtr->size)]->value);
    // if(delete(hashTablePtr, toon) == 0)
    // {
    //     printf("BAD\n");
    // }
    printf("[Info] (Searching) hashmap index: %s, value: %s\n", "town", search(hashTablePtr, "town"));
    printf("[Info] (Searching) hashmap index: %s, value: %s\n", hashTablePtr->items[3]->key, hashTablePtr->items[3]->value);

    delete(hashTablePtr, "tom");
    printf("[Info] (Searching) hashmap index: %s, value: %s\n", "town", search(hashTablePtr, "town"));

    
    exit(EXIT_SUCCESS);
}

