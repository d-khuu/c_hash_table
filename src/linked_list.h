/**
 * @file linked_list.h
 * @author Danny Khuu
 * @brief Header file for the linked list data
 *        structure and its functions
 * @version 0.1
 * @date 2023-04-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LinkedList_H
#define LinkedList_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @struct Node
 * @brief Linked list node struct
 * 
 * @var char * Node::key 
 * The key of the item
 * @var value * Node::value
 * The value associated with the key
 * @var Node * Node::prev
 * The previous node in the linked list
 * @var Node * Node::next
 * The next node in the linked list
 */
typedef struct Node
{
    char * key;
    char * value;
    struct Node * prev;
    struct Node * next;
}Node;

/**
 * @struct LinkedList
 * @brief The head of the linked list 
 * to indicate whatever metadata needed
 * 
 * @var Node * LinkedList::head
 * Head node of the linked list
 * @var unsigned int LinkedList::size
 * The size of the linked list
 */
typedef struct
{
    Node * head;
    unsigned int size;
}LinkedList;

/**
 * @brief Initialises the linked list
 * 
 * @param linkedList 
 * @return int 
 */
int initialise_ll(LinkedList* linkedList);


/**
 * @brief Inserts the node into the linked list
 * 
 * @param linkedList 
 * @param key 
 * @param value 
 * @return int 
 */
int insert_ll(LinkedList* linkedList, char* key, char* value);

/**
 * @brief Updates the node with a value
 *        based on its associated key
 * 
 * @param linkedList 
 * @param key 
 * @param value 
 * @return int 
 */
int update_ll(LinkedList* linkedList, char* key, char* value);

/**
 * @brief Deletes the linked list node
 *        based on the key
 * 
 * @param linkedList 
 * @param key 
 * @return int 
 */
int delete_ll(LinkedList* linkedList, char* key);

/**
 * @brief Searches the linked list for the value based
 *        on its associated key
 * 
 * @param linkedList 
 * @param key 
 * @return char* 
 */
char* search_ll(LinkedList* linkedList, char* key);

/**
 * @brief Prints the linked list in a very nice format :)
 * 
 * @param linkedList 
 */
void printLinkedList(LinkedList* linkedList);


/**
 * @brief Concatenates the strings in a more seemless way
 * 
 * @param str1 First string
 * @param str2 Second string
 * @return char* string = str1 + str2
 */
char* concatStr(char* str1, char* str2);

#endif