#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "MyDLL.h"

void MyDLLInit(DLL_List* dll) {
    dll->size=0;
    dll->Head = NULL;
    dll->Tail = NULL;
    for(int k=0;k<MAX_LIST_SIZE;k++){
        dll->nodes[k].key = 0;
    }    
}


int MyDLLInsert(DLL_List* dll, uint16_t key, uint8_t* data) {
    if (dll->size >= MAX_LIST_SIZE) {
        printf("\n\nError 1 -> List is full (The size of the list is %d)\n",MAX_LIST_SIZE);
        return FULL; // Não há espaço na DLL
    }
    MyDLL* newNode = NULL;
    for (int k=0;k<MAX_LIST_SIZE;k++){
        if(dll->nodes[k].key == 0){
           newNode = &dll->nodes[k];
        }
    }
    
    
    newNode->key = key;
    for (int i = 0; i < MAX_ELEM_SIZE; i++) {
        newNode->data[i] = data[i];
    }

    if (dll->size == 0) {
        dll->Head = dll->Tail = newNode;
    } else {
        dll->Tail->Next = newNode;
        newNode->Previous = dll->Tail;
        newNode->Next = NULL;
        dll->Tail = newNode;
    }
    dll->size++;
    return OK;
}

void MyDLLPrint(DLL_List* dll) {
    printf("\nDados na lista:\n");
    MyDLL* current = dll->Head;
    while (current != NULL) {
        printf("Chave: %d, Dados: %s\n", current->key, current->data);
        current = current->Next;
    }
}

MyDLL* MyDLLFind(DLL_List* dll, uint16_t key) {
    MyDLL* current = dll->Head;
    while(current->key != key){
      current = current->Next;
      if(current ==NULL){
      	printf("\nError 2 -> This key do not exist in this list\n");
       	return NotKey;
      }
    }
    printf("\nKey found !\nKey -> %d\nData-> %s\n",current->key,current->data);
    return current;
    
}

int MyDLLRemove(DLL_List* dll, uint16_t key) {
    MyDLL* current = dll->Head;
    MyDLL* previous = NULL;
    
    // Este while para se encontrar a chave, caso chega ao fim da lista e não encontre da erro
    while(current->key!=key){
      previous = current;
      current = current->Next;
      if(current == NULL){
      	printf("\nError 2 -> This key do not exist in this list\n");
       	return -1;
      }
    }
    current->key = 0;
    
    // Este else serve para o caso em que o no que queremos retirar é o primeiro
    if(previous != NULL){
    	previous->Next = current->Next;
    }else {
    	dll->Head = current->Next;
    }
    
    // Este else serve para o caso em que o no que queremos retirar é o ultimo
    if(current->Next != NULL){
    	current->Next->Previous = previous;
    } else {
    	dll->Tail = previous;
    } 
    
    dll->size--;
    
    return OK;
}

MyDLL* MyDLLFindNext(DLL_List* dll, uint16_t key) {
    MyDLL* current = MyDLLFind(dll, key);
    if (current == NULL) {
        printf("Error: Element with key %d not found\n", key);
        return NULL;
    }

    // Check if the current element is the last element in the list
    if (current->Next == NULL) {
        printf("Error: Current element with key %d is the last element in the list\n", key);
        return NULL;
    }

    return current->Next;
}

MyDLL* MyDLLFindPrevious(DLL_List* dll, uint16_t key) {
    MyDLL* current = MyDLLFind(dll, key);
    if (current == NULL) {
        printf("Error: Element with key %d not found\n", key);
        return NULL;
    }

    // Check if the current element is the last element in the list
    if (current->Previous == NULL) {
        printf("Error: Current element with key %d is the first element in the list\n", key);
        return NULL;
    }

    return current->Previous;
}

void swapNodes(MyDLL* a, MyDLL* b) {
    uint16_t tempKey = a->key;
    uint8_t tempData[MAX_ELEM_SIZE];

    memcpy(tempData, a->data, MAX_ELEM_SIZE);
    a->key = b->key;
    memcpy(a->data, b->data, MAX_ELEM_SIZE);
    b->key = tempKey;
    memcpy(b->data, tempData, MAX_ELEM_SIZE);
}

// Function to perform bubble sort on the doubly linked list
void MyDLLSortAscending(DLL_List* dll) {
    int swapped;
    MyDLL* ptr1;
    MyDLL* lptr = NULL;

    // Checking for empty list
    if (dll->Head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = dll->Head;

        while (ptr1->Next != lptr) {
            if (ptr1->key > ptr1->Next->key) {
                swapNodes(ptr1, ptr1->Next);
                swapped = 1;
            }
            ptr1 = ptr1->Next;
        }
        lptr = ptr1;
    } while (swapped);
}

void MyDLLSortDescending(DLL_List* dll) {
    int swapped;
    MyDLL* ptr1;
    MyDLL* lptr = NULL;

    // Checking for empty list
    if (dll->Head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = dll->Head;

        while (ptr1->Next != lptr) {
            if (ptr1->key < ptr1->Next->key) {
                swapNodes(ptr1, ptr1->Next);
                swapped = 1;
            }
            ptr1 = ptr1->Next;
        }
        lptr = ptr1;
    } while (swapped);
}

void MyDLLClear(DLL_List* dll) {
    // Reset list properties
    dll->Head = NULL;
    dll->Tail = NULL;
    dll->size = 0;
}

