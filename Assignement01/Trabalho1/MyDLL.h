#ifndef MYDLL_H
#define MYDLL_H

#include <stdint.h>

#define MAX_ELEM_SIZE 100
#define MAX_LIST_SIZE 10

typedef struct MyDLL {
    uint16_t key;
    uint8_t data[MAX_ELEM_SIZE];
    struct MyDLL* Next;
    struct MyDLL* Previous;
} MyDLL;

typedef struct DLL_List {
    MyDLL nodes[MAX_LIST_SIZE];
    MyDLL* Head;
    MyDLL* Tail;
    int size;
} DLL_List;

void MyDLLInit(DLL_List* dll);
int MyDLLInsert(DLL_List* dll, uint16_t key, uint8_t* data);
MyDLL* MyDLLFind(DLL_List* dll, uint16_t key);
int MyDLLRemove(DLL_List* dll, uint16_t key);
void MyDLLPrint(DLL_List* dll);

#endif
