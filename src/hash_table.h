/**
 * @file hash_table.h
 * @author Danny Khuu
 * @brief Header file for the hash table data 
 *        structure and its functions
 * @version 0.1
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "prime.h"

/**
 * @struct ht_item
 * @brief The hash table item struct
 * @var char * ht_item::key
 * The key for indexing the value
 * @var char * ht_item::value
 * The value/bucket associated to the key
 * 
 */
typedef struct
{
    char* key;
    char* value;
} ht_item;


/** 
 * @struct ht_hash_table
 * @brief The hash table struct
 * 
 * Refer to struct annotation here: https://stackoverflow.com/a/7210437
 * @var int ht_hash_table::size
 * The size of the hash table
 * @var int ht_hash_table::count
 * The current number of occupied buckets 
 * in the hash table
 * @var ht_item ** ht_hash_table::items
 * Member item of struct type ht_item
 */
typedef struct
{
    int size;
    int count;
    ht_item** items;
}ht_hash_table;

/**
 * @brief Initialise the hash table
 * 
 * @param hashTable The hash table instance
 * @param size      The initialised size of the hash table
 * @return int      The error code
 */
int initialiseHashTable(ht_hash_table* hashTable, int size);


/**
 * @brief Inserts a new item into the hash table
 * 
 * @param hashTable The hash table instance
 * @param key       The key to insert
 * @param value     The value to insert
 * @return int 
 */
int insert(ht_hash_table* hashTable, char* key, void* value);

/**
 * @brief Deletes the bucket with the given key
 * 
 * @param hashTable The hash table instance
 * @param key       The key associated to the bucket to delete
 * @return int      The exit code (0 = Failed to delete or 1 = Successfully deleted)
 */
int delete(ht_hash_table* hashTable, char* key);


/**
 * @brief Updates the value of the given key
 * 
 * @param hashTable The hash table instance
 * @param key       The key associated to the bucket to update
 * @param value     The value to update the bucket
 * @return int      The exit code (0 = Failed to update or 1 = Successfully updated)
 */
int update(ht_hash_table* hashTable, char* key, char* value);

/**
 * @brief Finds the bucket's index to place the data in
 * 
 * @param hashTable The hash table instance
 * @param key       The key associated to the bucket to search for
 * @return char*    The value associated to the key
 */
char* search(ht_hash_table* hashTable, char* key);


/**
 * @brief Get the Index object for the given key
 * 
 * @param hashTable The hash table instance
 * @param key       The key to find the associated index within the hash table
 * @return int      The index associated to the key
 */
int getIndex(ht_hash_table* hashTable, char* key);

/**
 * @brief Resizes the hashtable
 * 
 * @param hashTable The hash table instance
 * @return int      The exit code (0 = Failed to resize or 1 = Successfully resized)
 */
int resize(ht_hash_table* hashTable);

/**
 * @brief Calculates the hash of the key
 * 
 * @param hashTable The hash table instance
 * @param key       The key to base the hash calculation on
 * @param htLength  The length of the hash table
 * @return int      The calculated hash
 */
int hash(char* key, int htLength);

/**
 * @brief Checks if the hash table is full
 * 
 * @param hashTable The hash table instance
 * @return int      Boolean on whether it is full or not (1 = Full or 0 = Not full)
 */
int isFull(ht_hash_table* hashTable);


#endif