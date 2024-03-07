#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include "MyDLL.h"

void MyDLLInit(DLL_List* dll) {
    dll->Head = NULL;
    dll->Tail = NULL;
    dll->size = 0;
}

int MyDLLAdd(DLL_List* dll, uint16_t key, uint8_t* data) {
    if (dll->size >= MAX_LIST_SIZE) {
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
    dll->size++; // confirmar, pode estar mal
    return 0;
}

void MyDLLPrint(DLL_List* dll) {
    printf("Dados na lista:\n");
    MyDLL* current = dll->Head;
    while (current != NULL) {
        printf("Chave: %d, Dados: %s\n", current->key, current->data);
        current = current->Next;
    }
}

uint8_t* MyDLLFind(DLL_List* dll, uint16_t key) {
    return NULL; // Temporariamente retornando NULL
}
