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


int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Size not provided.\n");
    }
    else if(atoi(argv[1]) == 0)
    {
        printf("Invalid integer %s.\n",argv[1]);
        return 0;
    }
    
    int SIZE_G = atoi(argv[1]);
    int exitCode;

    exitCode = isPrime(SIZE_G);
    if(exitCode == 1)
    {
        printf("The value %d is a prime number.\n", SIZE_G);
        // int nextPrime = generatePrime(SIZE_G);
        // printf("Here is the next prime number -> %d.\n", nextPrime);
    }
    else
    {
        printf("The value %d is not a prime number.\n", SIZE_G);
        SIZE_G = generatePrime(SIZE_G);
        printf("We'll generate one for you. Here, it will be %d.\n", SIZE_G);
    }
    
    ht_hash_table* hashTablePtr = malloc(sizeof(*hashTablePtr));

    if(initialiseHashTable(hashTablePtr, SIZE_G) != 0)
    {
        printf("Error: Failed to initialise the hash table.\n");
    }
    printf("Hash Table Size: %d, Count: %d.\n", hashTablePtr->size, hashTablePtr->count);

    char * keyTest = "donut";
    void * valTest = "valueTest";
    printf("%s\n",keyTest);

    char * toon = "toonj";
    void * val = "kingdom";
    printf("hash of new is %d\n", hash(toon, hashTablePtr->size));
    
    insert(hashTablePtr, keyTest, valTest);
    insert(hashTablePtr, toon, val);
    // keyTest = (char *)malloc(20);
    // strcpy(keyTest, "fake");
    printf("%s\n",keyTest);
    printf("%d\n",hash(keyTest, hashTablePtr->size));
    printf("key => %s = %d, item => %s\n", keyTest, hash(keyTest, hashTablePtr->size), hashTablePtr->items[hash(keyTest, hashTablePtr->size)]->value);
    if(delete(hashTablePtr, toon) == 0)
    {
        printf("BAD\n");
    }
    printf("hashmap index: %s, value: %s\n", keyTest, search(hashTablePtr, keyTest));
    return 0;
}