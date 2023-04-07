/**
 * @file hash_table.h
 * @author Danny Khuu
 * @brief 
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
 * @brief This is the hash table item struct
 * @var ht_item::key
 * The key as a string.
 * @var ht_item::value
 * The value associated to the key.
 * 
 */
typedef struct
{
    char* key;
    char* value;
} ht_item;


/** 
 * @struct ht_hash_table
 * @brief This is the hash table struct
 * @var ht_hash_table::size
 * Member 'size' is the size of the hash table
 * @var ht_hash_table::count
 * Member 'count' is the current number of occupied buckets 
 * in the hash table
 * @var ht_hash_table::items
 * Member item of struct type ht_item
 * 
 * Refer to struct annotation here: https://stackoverflow.com/a/7210437
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
 * @brief Inserts 
 * 
 * @param hashTable 
 * @param key 
 * @param value 
 * @return int 
 */
int insert(ht_hash_table* hashTable, char* key, void* value);

/**
 * @brief Deletes the bucket with the given key
 * 
 * @param hashTable 
 * @param key 
 * @return int 
 */
int delete(ht_hash_table* hashTable, char* key);


/**
 * @brief Updates the value of the given key
 * 
 * @param hashTable 
 * @param key 
 * @param value 
 * @return int 
 */
int update(ht_hash_table* hashTable, char* key, char* value);

/**
 * @brief Finds the bucket's index to place the data in
 * 
 * @param hashTable 
 * @param key 
 * @return char* 
 */
char* search(ht_hash_table* hashTable, char* key);


/**
 * @brief Get the Index object for the given key
 * 
 * @param hashTable 
 * @param key 
 * @return int 
 */
int getIndex(ht_hash_table* hashTable, char* key);

/**
 * @brief Resizes the hashtable
 * 
 * @param hashTable 
 * @return int 
 */
int resize(ht_hash_table* hashTable);

/**
 * @brief Calculates the hash of the key
 * 
 * @param hashTable
 * @param key 
 * @param htLength
 * @return int 
 */
int hash(char* key, int htLength);

/**
 * @brief Checks if the hash table is full
 * 
 * @param hashTable 
 * @return int 
 */
int isFull(ht_hash_table* hashTable);


#endif