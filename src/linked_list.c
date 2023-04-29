/**
 * @file linked_list.c
 * @author Danny Khuu
 * @brief C file for the linked list data structure and functions
 * @version 0.1
 * @date 2023-04-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "linked_list.h"

int initialise_ll(LinkedList* linkedList)
{
    linkedList->size = 0;
    linkedList->head = NULL;
    return 1;
}

int insert_ll(LinkedList* linkedList, char* key, char* value)
{
    Node* tempNode = malloc(sizeof(*tempNode));
    LinkedList * headNode = linkedList;
    tempNode->key = strdup(key);
    tempNode->value = strdup(value);

    Node* currNode = linkedList->head;
    Node* prevNode = NULL;
    int resultCmp;
    
    // Insert at head
    if(linkedList->head == NULL)
    {
        tempNode->prev = tempNode;
        tempNode->next = NULL;
        linkedList->head = tempNode;
        headNode->size ++;
        printf("[Info] Inserted node in linkedlist with key: %s value: %s\n", key, value);
        return 1;
    }
    else
    {
        do
        {
            resultCmp = strcmp(currNode->key, key);
            // ll key and key are the same
            if(resultCmp == 0)
            {
                printf("The key already exists within the bucket");
                free(tempNode);
                return 0;
            }
            // Found the spot ll key is higher than temp key
            else if(resultCmp > 0)
            {
                tempNode->next = currNode;
                tempNode->prev = prevNode;
                currNode->prev = tempNode;
                if(prevNode != NULL) prevNode->next = tempNode;
                if(currNode == headNode->head) headNode->head = tempNode;
                headNode->size ++;
                printf("[Info] Inserted node in linkedlist with key: %s value: %s\n", key, value);
                return 1;
            }
            // Next is null, so insert
            else if(currNode->next == NULL)
            {
                currNode->next = tempNode;
                tempNode->prev = currNode;
                tempNode->next = NULL;
                headNode->size ++;
                printf("[Info] Inserted node in linkedlist with key: %s value: %s\n", key, value);
                return 1;
            }
            prevNode = currNode;
            currNode = currNode->next;
        } while (currNode != NULL);
        
        printf("[Error] Invalid state, failed to insert in linked list. Key: %s \n", key);
        return 0;
    }
}

int update_ll(LinkedList* linkedList, char* key, char* value)
{
    int resComp;
    char * prevVal;
    Node* currNode = linkedList->head;

    if(linkedList->head == NULL)
    {
        printf("[Warning] There is nothing in this linked list to be updated. Key: %s Val: %s\n",key, value);
        return 0;
    }
    else
    {
        do
        {
            resComp = strcmp(currNode->key, key);
            if(resComp == 0)
            {
                prevVal = currNode->value;
                currNode->value = strdup(value);
                printf("[Info] Updated node key: %s with value %s from %s\n", key, value, prevVal);
                return 1;
            }
            else if(resComp > 0)
            {
                printf("[Warning] The key %s could not be found in the bucket\n", key);
                return 0;
            }
            currNode = currNode->next;
        }while(currNode != NULL);
        printf("[Warning] The key %s could not be found in the bucket\n", key);
        return 0;
    }
    return 0;
}


int delete_ll(LinkedList* linkedList, char* key)
{
    int resComp;
    Node* prevNode = NULL;
    Node* currNode = linkedList->head;
    LinkedList* linkedListHead = linkedList;

    if(linkedList->head == NULL)
    {
        printf("[Warning] The key does not exists in the bucket (The linked list is empty)\n");
        return 0;
    }
    else
    {
        do
        {
            resComp = strcmp(currNode->key, key);
            // printf("[Debug] rescomp %d key %s arg %s\n", resComp, key, currNode->key);
            if(resComp == 0)
            {
                if(currNode == linkedListHead->head)
                {
                    linkedListHead->head = currNode->next;
                    if(currNode->next != NULL)
                    {
                        currNode->next->prev = prevNode;
                    }
                    free(currNode);
                    linkedListHead->size --;
                }
                else
                {
                    prevNode->next = currNode->next;
                    if(currNode->next != NULL)
                    {
                        currNode->next->prev = prevNode;
                    }
                    free(currNode);
                    linkedListHead->size --;
                }
                printf("[Info] Delete node with key %s in linkedlist\n", key);
                return 1;
            }
            else if(resComp > 0)
            {
                printf("[Warning] The key %s could not be found in the bucket\n", key);
                return 0;
            }
            prevNode = currNode;
            currNode = currNode->next;
        }while(currNode != NULL);
        printf("[Warning] The key %s could not be found in the bucket\n", key);
        return 0;
    }
    return 0;
}

char* search_ll(LinkedList* linkedList, char* key)
{
    int resComp;
    Node* currNode = linkedList->head;
    
    if(linkedList->head == NULL)
    {
        printf("[Warning] There is nothing in this linkedlist to be searched for. Key %s\n", key);
    }
    else
    {
        do
        {
            resComp = strcmp(currNode->key, key);
            if(resComp == 0)
            {
                return currNode->value;
            }
            else if(resComp > 0)
            {
                printf("[Warning] The key %s could not be found in the bucket (Early Termination)\n", key);
                return NULL;
            }
            currNode = currNode->next;
        }while(currNode != NULL);
        printf("[Warning] The key %s could not be found in the bucket\n", key);
        return NULL;
    }
    return NULL;
}


void printLinkedList(LinkedList* linkedList)
{
    Node* currNode = linkedList->head;
    int i = 0;

    printf("\n======================================================================\n");
    printf("Printing Linked List\n");
    printf("Size: %d\n", linkedList->size);

    if(currNode == NULL)
    {
        printf("EMPTY\n");
        return;
    }
    else
    {
        printf("Index\tKey\tValue\tAddress\t\tPrev\t\tNext\n");
        while(currNode != NULL)
        {
            printf("%d\t%s\t%s\t%p\t%p\t%p\n", i, currNode->key, 
                                                currNode->value,
                                                (void*) currNode, 
                                                (void*) currNode->prev, 
                                                (void*) currNode->next);
            i ++;
            currNode = currNode->next;
        }
    }


    printf("======================================================================\n\n");

    return;
}

char* concatStr(char* str1, char* str2)
{
    char* retStr;

    if((retStr = malloc(strlen(str1) + strlen(str2))) != NULL)
    {
        retStr[0] = '\0';
        strcat(retStr, str1);
        strcat(retStr, str2);
    }
    else
    {
        fprintf(stderr,"[Error] Could not malloc\n");
        exit(EXIT_FAILURE);
    }

    return retStr;
}