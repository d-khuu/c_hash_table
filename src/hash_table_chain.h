/**
 * @file hash_table_chain.h
 * @author Danny Khuu
 * @brief Header file for the separate chaining hash table data 
 *        structure and its functions
 * @version 0.1
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef HASH_TABLE_CHAIN
#define HASH_TABLE_CHAIN

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "prime.h"
#include "linked_list.h"

/**
 * @brief Java likes this number as the 
 * initial size
 * 
 */
#define DEFAULT_INITIAL_CAPACITY 1<<4

/**
 * @brief The load factor of the hash
 * table
 * 
 */
#define LOAD_FACTOR 0.75


/** 
 * @struct HashTable
 * @brief The hash table struct
 * 
 * Refer to struct annotation here: https://stackoverflow.com/a/7210437
 * @var int HashTable::size
 * The size of the hash table
 * @var int HashTable::count
 * The current number of occupied buckets (largely useless)
 * in the hash table
 * @var LinkedList** HashTable::items
 * Member item of struct type LinkedList
 */
typedef struct
{
    int size;
    int count;
    LinkedList** items;
}HashTable;

/**
 * @brief Initialise the hash table
 * 
 * @param hashTable The hash table instance
 * @param size      The initialised size of the hash table
 * @return int      The error code
 */
int initialise_ht(HashTable* hashTable, int size);


/**
 * @brief Inserts a new item into the hash table
 * 
 * @param hashTable The hash table instance
 * @param key       The key to insert
 * @param value     The value to insert
 * @return int 
 */
int insert_ht(HashTable* hashTable, char* key, void* value);

/**
 * @brief Deletes the bucket with the given key
 * 
 * @param hashTable The hash table instance
 * @param key       The key associated to the bucket to delete
 * @return int      The exit code (0 = Failed to delete or 1 = Successfully deleted)
 */
int delete_ht(HashTable* hashTable, char* key);


/**
 * @brief Updates the value of the given key
 * 
 * @param hashTable The hash table instance
 * @param key       The key associated to the bucket to update
 * @param value     The value to update the bucket
 * @return int      The exit code (0 = Failed to update or 1 = Successfully updated)
 */
int update_ht(HashTable* hashTable, char* key, char* value);

/**
 * @brief Finds the bucket's index to place the data in
 * 
 * @param hashTable The hash table instance
 * @param key       The key associated to the bucket to search for
 * @return char*    The value associated to the key
 */
char* search_ht(HashTable* hashTable, char* key);

/**
 * @brief Resizes the hashtable
 * 
 * @param hashTable The hash table instance
 * @return int      The exit code (0 = Failed to resize or 1 = Successfully resized)
 */
int resize_ht(HashTable* hashTable);

/**
 * @brief Calculates the hash of the key
 * 
 * @param key       The key to base the hash calculation on
 * @param htLength  The length of the hash table
 * @return int      The calculated hash
 */
int hash_ht(char* key, int htLength);

/**
 * @brief Initialises the size integer
 * 
 * @param size The size to check and initialise
 * @return int The valid size integer to initialise with
 */
int initSize_ht(int size);

/**
 * @brief Checks if the hash table bucket's linkedlist exceeds the load factor
 * 
 * @param hashTable The hash table instance
 * @param hashValue The hash value to find bucket
 * @return int      Boolean on whether it is full or not (1 = Full or 0 = Not full)
 */
int isFull_ht(HashTable* hashTable, int hashValue);


#endif