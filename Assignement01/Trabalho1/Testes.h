#ifndef TESTES_H
#define TESTES_H

/** \file Testes.h
 *  \brief This file contains declarations of functions for testing the MyDLL functionality.
 *
 *  This file declares several test functions to verify the functionality of the MyDLL library. 
 *  These functions perform various operations such as insertion, removal, searching, and sorting 
 *  on a doubly linked list-based database implemented using the MyDLL library.
 *
 *  \author Pedro Afonso 104206
 *  \author Carlos Teixeira 103187
 *  \date 12/03/2024
 */

#include <stdint.h>
#include "MyDLL.h"

/**
 *  \brief Perform Test 1: Removal of a node from the doubly linked list.
 *  
 *  This function verifies the removal of a node from the doubly linked list.
 *
 *  \param index Index of the key to be removed from the list.
 *  \return This function prints the contents of the list after the removal.
 */
void Teste1(int index);

/**
 *  \brief Perform Test 2: Insertion of multiple nodes into the doubly linked list, and when this it's full it returns an error. 
 *  
 *  This function verifies the insertion of multiple nodes into the doubly linked list.
 *  \return This function prints the contents of the list after the insertion.
 */
void Teste2();

/**
 *  \brief Perform Test 3: Searching functionality of the doubly linked list.
 *  
 *  This function verifies the searching functionality of the doubly linked list.
 *
 *  \param x The key to be searched in the list.
 *  \return This function returns the node that was searched.
 */
void Teste3(int x);

/**
 *  \brief Perform Test 4: Removal and insertion operations together.
 *  
 *  This function verifies the removal and insertion operations together in the doubly linked list.
 *
 *  \param index Index of the key to be removed from the list.
 *  \return This function prints the contents of the list after the removal and insertion.
 */
void Teste4(int index);

/**
 *  \brief Perform Test 5: Menu-driven interface to interact with the doubly linked list.
 *  
 *  This function provides a menu-driven interface to interact with the doubly linked list.
 */
void Teste5();

/**
 *  \brief Perform Test 6: Finding the next and previous nodes in the list.
 *  
 *  This function verifies the functionality of finding the next and previous nodes in the list.
 *  \return This function returns the node of next and the previous of the key that was selected.
 */
void Teste6();

/**
 *  \brief Perform Test 7: Sorting functionality of the doubly linked list.
 *  
 *  This function verifies the sorting functionality of the doubly linked list.
 *  \return This function prints the contents of the list after the sorting in both ascending and descending ways.
 */
void Teste7();

#endif
