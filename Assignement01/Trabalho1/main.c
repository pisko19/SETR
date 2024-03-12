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
   
    for (int k = 0; k < List_Elements-1; k++) {
        int full = MyDLLInsert(&dll, keys[k], datas[k]); // Add nodes to the DLL
        if(full==-1){
           break;
           }
        
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

void Teste4 (int index){
    #define List_Elements 6
    DLL_List dll;
    MyDLLInit(&dll); // Initialize the DLL
    
    uint16_t keys[List_Elements] = {100, 105, 1078, 102, 154, 200};
    uint8_t datas[List_Elements][MAX_ELEM_SIZE] = {"Pedro, 103457", "Carlos,103187", "Americo,45412", "João,87412", "Romario,45872", "JOSE,541256"};
   
    for (int k = 0; k < List_Elements; k++) {
        MyDLLInsert(&dll, keys[k], datas[k]); // Add nodes to the DLL
    }
    printf("\nBEFORE REMOVE\n");
    MyDLLPrint(&dll);
    MyDLLRemove(&dll,keys[index]);
    printf("\nAFTER REMOVE\n");
    MyDLLPrint(&dll);
    MyDLLInsert(&dll,512,"Maria,784521");
    printf("\nAFTER NEW INSERT\n");
    MyDLLPrint(&dll);
}

void Teste5(){
    int select = -1;
    DLL_List dll;
    MyDLLInit(&dll); // Initialize the DLL
    uint16_t key;
    uint8_t data;
    
    while(select != 0){
      printf("\n"
             " ##########################\n"
             " #                        #\n"
             " # 0 -> EXIT              #\n"
             " # 1 -> LER OS DADOS      #\n"
             " # 2 -> ACRESCENTAR DADOS #\n"
             " # 3 -> REMOVER DADOS     #\n"
             " # 4 -> ENCONTRAR DADOS   #\n"
             " #                        #\n"
             " ##########################\n");

      scanf("%d",&select);
      switch(select){
        case(1):
           MyDLLPrint(&dll);
           break;
      
        case(2):
           if(dll.size < MAX_LIST_SIZE){
              printf("\n What is your key ?\n");
              scanf("%hd",&key);
              printf("\n What is your data ?\n");
              scanf("%s",&data);
              int x = MyDLLInsert(&dll,key,&data);
              if(x==0){
                 printf("\nThe list have %d elements\n",dll.size);
              }
              MyDLLPrint(&dll);
              break;
            } else {
              printf("\n The list is already full\n");
              break;
      
            }
            
          case(3):
            if (dll.size != 0){
              printf("\n What is the key that you want to remove ?\n");
              scanf("%hd",&key);
              MyDLLRemove(&dll,key);
            } else {
              printf("\n The list is empty\n");
            }
            
       }
     }
}

int main() {
    int teste = 4;
    int x;
    switch(teste){
    	case(1):
    	printf("\nWhat element of the list you want to delete ? (1 to 6)\n");
    	scanf("%d",&x);
    	Teste1(x-1);
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
        // Este codigo da erro ao introduzir um novo elemento 
        printf("\nWhat element of the list you want to delete ? (1 to 6)\n");
    	scanf("%d",&x);
        Teste4(x-1);
        break;
        
        case(5):
        Teste5();
        break;
        
    
    }
    return 0;
}

