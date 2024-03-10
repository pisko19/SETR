#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "MyDLL.h"

void MyDLLInit(DLL_List* dll) {
    static DLL_List static_dll; // Static instance of DLL_List
    static_dll.size = 0;
    *dll = static_dll; // Copy the static instance to the provided pointer
    
}


int MyDLLInsert(DLL_List* dll, uint16_t key, uint8_t* data) {
    if (dll->size >= MAX_LIST_SIZE) {
        printf("\n\nError 1 -> List is full (The size of the list is %d)\n",MAX_LIST_SIZE);
        return -1; // Não há espaço na DLL
    }
    
    MyDLL* newNode = &dll->nodes[dll->size];
    newNode->key = key;
    for (int i = 0; i < MAX_ELEM_SIZE; i++) {
        newNode->data[i] = data[i];
    }

    if (dll->size == 0) {
        dll->Head = dll->Tail = newNode;
    } else {
        dll->Tail->Next = newNode;
        newNode->Previous = dll->Tail;
        dll->Tail = newNode;
    }
    dll->size++;
    return 0;
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
       	return NULL;
      }
    }
    printf("\nKey found !\nKey -> %d\nData->%s\n",current->key,current->data);
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
    
    return 0;
      
    	
}

