#ifndef MYDLL_H
#define MYDLL_H

#include <stdint.h>

#define MAX_ELEM_SIZE 100
#define MAX_LIST_SIZE 50

typedef struct MyDLL {
    uint16_t key;
    uint8_t data[MAX_ELEM_SIZE];
    struct MyDLL* Next;
    struct MyDLL* Previous;
} MyDLL;

typedef struct DLL_List {
    MyDLL nodes[MAX_LIST_SIZE];
    MyDLL* Head; // está mal, verificar
    MyDLL* Tail;  // da para fazer com array
    int size;
} DLL_List;

void MyDLLInit(DLL_List* dll);
int MyDLLAdd(DLL_List* dll, uint16_t key, uint8_t* data);
uint8_t* MyDLLFind(DLL_List* dll, uint16_t key);
void MyDLLPrint(DLL_List* dll);

#endif
