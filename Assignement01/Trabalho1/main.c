#include <stdio.h>
#include "MyDLL.h"

void Teste1 (int index){
    #define List_Elements 6
    DLL_List dll;
    MyDLLInit(&dll); // Initialize the DLL
    
    uint16_t keys[List_Elements] = {100, 105, 1078, 102, 154, 200};
    uint8_t datas[List_Elements][MAX_ELEM_SIZE] = {"Pedro,103457", "Carlos,103187", "Americo,45412", "João,87412", "Romario,45872", "JOSE,541256"};
   
    for (int k = 0; k < List_Elements; k++) {
        MyDLLInsert(&dll, keys[k], datas[k]); // Add nodes to the DLL
    }
    
    // Print the data in the list
    printf("\nBEFORE REMOVE\n");
    MyDLLPrint(&dll);
    MyDLLRemove(&dll,keys[index]);
    printf("\nAFTER REMOVE\n");
    MyDLLPrint(&dll);
}

void Teste2 (){
    #define List_Elements 12
    DLL_List dll;
    MyDLLInit(&dll); // Initialize the DLL
    uint16_t keys[List_Elements] = {100,105,1078,102,154,200,45,421,120,156,7541,452};
    uint8_t datas[List_Elements][MAX_ELEM_SIZE] = {"Pedro,103457", "Carlos,103187", "Americo,45412", "João,87412", "Romario,45872", "JOSE,541256","Antonio,141524", "Maria,104527", "Joana,44522", "Ines,872", "Ana,47522", "Jacinta,54526"};
   
    for (int k = 0; k < List_Elements; k++) {
        int full = MyDLLInsert(&dll, keys[k], datas[k]); // Add nodes to the DLL
        if(full==-1)
           break;
        
    }
    
    // Print the data in the list

    MyDLLPrint(&dll);

}

void Teste3 (int x){
    #define List_Elements 6
    DLL_List dll;
    MyDLLInit(&dll); // Initialize the DLL
    
    uint16_t keys[List_Elements] = {100, 105, 1078, 102, 154, 200};
    uint8_t datas[List_Elements][MAX_ELEM_SIZE] = {"Pedro,103457", "Carlos,103187", "Americo,45412", "João,87412", "Romario,45872", "JOSE,541256"};
   
    for (int k = 0; k < List_Elements; k++) {
        MyDLLInsert(&dll, keys[k], datas[k]); // Add nodes to the DLL
    }
    
    MyDLL* find = MyDLLFind(&dll,x);

}

void Teste4 (){
    #define List_Elements 6
    DLL_List dll;
    MyDLLInit(&dll); // Initialize the DLL
    
    uint16_t keys[List_Elements] = {100, 105, 1078, 102, 154, 200};
    uint8_t datas[List_Elements][MAX_ELEM_SIZE] = {"Pedro,103457", "Carlos,103187", "Americo,45412", "João,87412", "Romario,45872", "JOSE,541256"};
   
    for (int k = 0; k < List_Elements; k++) {
        MyDLLInsert(&dll, keys[k], datas[k]); // Add nodes to the DLL
    }
    printf("\nBEFORE REMOVE\n");
    MyDLLPrint(&dll);
    MyDLLRemove(&dll,keys[2]);
    MyDLLInsert(&dll,512,"Maria,784521");
    printf("\nAFTER REMOVE\n");
    MyDLLPrint(&dll);
}


int main() {
    int teste = 4;
    int x;
    switch(teste){
    	case(1):
    	printf("\nWhat element of the list you want to delete ? (0 to 5)\n");
    	scanf("%d",&x);
    	Teste1(x);
    	break;
    	
    	case(2):
    	Teste2();
    	break;
    	
    	case(3):
    	printf("\nWhat is the key number that you want to find ?\n");
    	scanf("%d",&x);
    	Teste3(x);
    	break;
        
        case(4):
        Teste4();
        break;
    
    }
    return 0;
}

