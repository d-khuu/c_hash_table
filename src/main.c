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
    // char* str = "dude";

    // int result = hash(str);

    // printf("Result: %d for string %s\n", result, str);
    
    ht_hash_table* hashTablePtr = malloc(sizeof(*hashTablePtr));

    exitCode = initialiseHashTable(hashTablePtr, SIZE_G);

    if(exitCode != 0)
    {
        printf("Error: Failed to initialise the hash table.\n");
    }
    // printf("Exit Code: %d\n", exitCode);

    printf("Hash Table Size: %d, Count: %d.\n", hashTablePtr->size, hashTablePtr->count);

    return 0;
}