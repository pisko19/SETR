#ifndef MYDLL_H
#define MYDLL_H

/** \file MyDLL.h
 *  \brief This file contains all the structures and functions needed for the database creation.
 *
 *  Detailed description starts here.
 *
 *  \author Pedro Afonso, 104206
 *  \author Carlos Teixeira, 103187
 *  \date 10/3/2024
 *  \bug There are no known bugs.
 */

/*Includes*/
#include <stdint.h>

#define MAX_ELEM_SIZE 100 /**< Maximum size of the data element */
#define MAX_LIST_SIZE 8 /**< Maximum number of nodes in the list */
#define FULL -1
#define OK 0
#define NotKey NULL

/**
 *  \struct MyDLL
 *  \brief A structure representing a doubly linked list node.
 */
typedef struct MyDLL {
    uint16_t key; /**< The key associated with the node */
    uint8_t data[MAX_ELEM_SIZE]; /**< The data stored in the node */
    struct MyDLL* Next; /**< Pointer to the next node */
    struct MyDLL* Previous; /**< Pointer to the previous node */
} MyDLL;

/**
 *  \struct DLL_List
 *  \brief A structure representing a doubly linked list.
 */
typedef struct DLL_List {
    MyDLL nodes[MAX_LIST_SIZE]; /**< Array of nodes in the list */
    MyDLL* Head; /**< Pointer to the head of the list */
    MyDLL* Tail; /**< Pointer to the tail of the list */
    int size; /**< Current size of the list */
} DLL_List;

/**
 *  \brief Initialize a doubly linked list.
 *  \param dll Pointer to the doubly linked list.
 */
void MyDLLInit(DLL_List* dll);

/**
 *  \brief Insert a new node into the doubly linked list.
 *  \param dll Pointer to the doubly linked list.
 *  \param key The key associated with the new node.
 *  \param data Pointer to the data to be stored in the new node.
 *  \return 1 if successful, 0 otherwise.
 */
int MyDLLInsert(DLL_List* dll, uint16_t key, uint8_t* data);

/**
 *  \brief Find a node in the doubly linked list by its key.
 *  \param dll Pointer to the doubly linked list.
 *  \param key The key of the node to find.
 *  \return Pointer to the node if found, NULL otherwise.
 */
MyDLL* MyDLLFind(DLL_List* dll, uint16_t key);

/**
 *  \brief Remove a node from the doubly linked list by its key.
 *  \param dll Pointer to the doubly linked list.
 *  \param key The key of the node to remove.
 *  \return a DLL List.
 */
int MyDLLRemove(DLL_List* dll, uint16_t key);

/**
 *  \brief Print the contents of the doubly linked list.
 *  \param dll Pointer to the doubly linked list.
 */
void MyDLLPrint(DLL_List* dll);


/**
 *  \brief Find the next node in the doubly linked list based on the key.
 *  \param dll Pointer to the doubly linked list.
 *  \param key The key of the current node.
 *  \return Pointer to the next node if found, NULL otherwise.
 */
MyDLL* MyDLLFindNext(DLL_List* dll, uint16_t key);

/**
 *  \brief Find the previous node in the doubly linked list based on the key.
 *  \param dll Pointer to the doubly linked list.
 *  \param key The key of the current node.
 *  \return Pointer to the previous node if found, NULL otherwise.
 */
MyDLL* MyDLLFindPrevious(DLL_List* dll, uint16_t key);

/**
 *  \brief Sort the doubly linked list in ascending order based on the keys.
 *  \param dll Pointer to the doubly linked list.
 */
void MyDLLSortAscending(DLL_List* dll);

/**
 *  \brief Sort the doubly linked list in descending order based on the keys.
 *  \param dll Pointer to the doubly linked list.
 */
void MyDLLSortDescending(DLL_List* dll);

/**
 *  \brief Swap the data of two nodes in the list.
 *  \param a Pointer to the first node.
 *  \param b Pointer to the second node.
 */
void swapNodes(MyDLL* a, MyDLL* b);

void MyDLLClear(DLL_List* dll);

#endif
