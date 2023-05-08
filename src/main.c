/**
 * @file main.c
 * @author Danny Khuu
 * @brief The main C file to interact with the hash table for testing
 * @version 0.1
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "hash_table.h"

/**
 * @brief Static file name
 * to load data from
 * 
 */
#define FILE_NAME "data.csv"

#ifdef OLD
#include "hash_table.h"
#else
#include "hash_table_chain.h"
#endif


/**
 * @brief Loads the data from the csv file into the hashtable
 * 
 * @param hashTable The hash table instance
 * @return int The exit code (0 = Failed or 1 = Successful)
 */
int load_from_file(HashTable* hashTable)
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
        insert_ht(hashTable, keyTemp, valueTemp);
        // if(isFull_ht(hashTable))
        // {
        //     printf("[Warning] The hashtable is full\n");
        //     // break;
        // }
    }
    // printf("[Info] hashmap index: %s, value: %s\n", "town", search_ht(hashTable, "town"));
    // printf("hashmap index: %s, value: %s\n", hashTable->items[1]->key, hashTable->items[1]->value);
    // printf("[Info] hashmap index: %s, value: %s\n", keyTemp, search_ht(hashTable, keyTemp));
    printf("[Info] Complete import\n");
    fclose(fptr);
    // exit(0);
    return 1;
}

/**
 * @brief Reads the arguments and returns the init hashmap size
 * 
 * @param argc Argument count
 * @param argv Arguments in an array
 * @return int 
 */
int read_args(int argc, char *argv[])
{
    if(argc > 1)
    {
        if(atoi(argv[1]) <= 0)
        {
            printf("[Error] Invalid integer %s.\n",argv[1]);
            exit(EXIT_FAILURE);
        }
        return atoi(argv[1]);
    }
    return 0;
}


// int playWithLL()
// {
    
//     LinkedList* linkedList = malloc(sizeof(*linkedList));

//     initialise_ll(linkedList);

//     insert_ll(linkedList, "Char", "zaku");
//     printLinkedList(linkedList);
//     insert_ll(linkedList, "Amuro", "rx-78-2");
//     printf("Searching: %s\n",search_ll(linkedList, "amuro"));
//     printLinkedList(linkedList);
//     insert_ll(linkedList, "Kamille", "Zeta");
//     insert_ll(linkedList, "Judau", "ZZ");
//     insert_ll(linkedList, "Amuro", "nu");
//     insert_ll(linkedList, "Quattro", "Hyaku Shiki");
//     printLinkedList(linkedList);
//     delete_ll(linkedList, "char");


//     return 1;
// }


int normalOperations(int argc, char *argv[])
{
    int initSize_ht = read_args(argc, argv);
    HashTable* hashTablePtr = malloc(sizeof(*hashTablePtr));

    if(initialise_ht(hashTablePtr, initSize_ht) != 1)
    {
        printf("[Error] Failed to initialise the hash table.\n");
        exit(EXIT_FAILURE);
    }
    printf("[Info] Hash Table Size: %d, Count: %d.\n", hashTablePtr->size, hashTablePtr->count);
    
    load_from_file(hashTablePtr);

    printf("[Info] (Searching) hashmap index: %s, value: %s\n", "town", search_ht(hashTablePtr, "town"));
    // printf("[Info] (Searching) hashmap index: %s, value: %s\n", hashTablePtr->items[15]->key, hashTablePtr->items[15]->value);
    // printLinkedList(hashTablePtr->items[0]);
    delete_ht(hashTablePtr, "fun");
    // printLinkedList(hashTablePtr->items[0]);
    delete_ht(hashTablePtr, "town");
    printf("[Info] (Searching) hashmap index: %s, value: %s\n", "town", search_ht(hashTablePtr, "town"));

    return 1;
}

/**
 * @brief The main function just for testing the hash table
 * 
 * @param argc The number of arguments passed
 * @param argv The argument values
 * @return int 
 */
int main(int argc, char *argv[])
{
    // playWithLL();
    normalOperations(argc, argv);

    
    exit(EXIT_SUCCESS);
}


