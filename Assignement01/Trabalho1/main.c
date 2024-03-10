#include <stdio.h>
#include "MyDLL.h"

#define List_Elements 6
int main() {
    DLL_List dll;
    MyDLLInit(&dll); // Initialize the DLL

    // Arrays of keys and data
    uint16_t keys[List_Elements] = {100, 105, 1078, 102, 154, 200};
    uint8_t datas[List_Elements][MAX_ELEM_SIZE] = {"Pedro,103457", "Carlos,103187", "Americo,45412", "João,87412", "Romario,45872", "JOSE,541256"};
   
    for (int k = 0; k < List_Elements; k++) {
        MyDLLInsert(&dll, keys[k], datas[k]); // Add nodes to the DLL
    }
    
    // Print the data in the list
    MyDLLPrint(&dll);

    //MyDLLFind(&dll,99);
    
    MyDLLRemove(&dll,keys[6]);
    MyDLLPrint(&dll);
    return 0;
}

