#include <stdio.h>
#include "Testes.h"

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
    MyDLL *Found;
    DLL_List dll;
    MyDLLInit(&dll); // Initialize the DLL
    uint16_t key;
    uint8_t data;
    int x;

    while(1){
      if(select==0)
         break;
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
        case(0):
           printf("\n\n END\n\n");
           break;
        case(1):
           if (dll.size != 0){
              MyDLLPrint(&dll);
              break;
           } else {
              printf("\n\n THE LIST IS EMPTY\n\n");
              break;
           }
      
        case(2):
           if(dll.size < MAX_LIST_SIZE){
              int num;
              printf("\nWhat is your key ?\n");
              scanf("%d",&num);
              printf("\nWhat is your data ?\n");
              scanf("%s",&data);
   
              x = MyDLLInsert(&dll,num,&data);
              if(x==0){
                 printf("\nThe list have %d elements\n",dll.size);
              }
              MyDLLPrint(&dll);
              break;
            } else {
              printf("\n THE LIST IS ALREADY FULL\n");
              break;
      
            }
            
          case(3):
            if (dll.size != 0){
              printf("\n What is the key that you want to remove ?\n");
              scanf("%d",&key);
              MyDLLRemove(&dll,key);
              break;
            } else {
              printf("\n\n THE LIST IS EMPTY\n\n");
              break;
            }
          
          case(4):
            if (dll.size != 0){
              printf("\nWhat is the key that you want to find ?\n");
              scanf("%d",&key);
              Found = MyDLLFind(&dll,key);
              
              break;
            } else {
              printf("\n\n THE LIST IS EMPTY\n\n");
              break;
            }
            
          default:
            printf("\nNUMERO ERRADO\n");
            break;
            
       }
     }
}


void Teste6()
{
  #define List_Elements 6
  DLL_List dll;
  MyDLLInit(&dll); // Initialize the DLL 
  uint16_t keys[List_Elements] = {100, 105, 1078, 102, 154, 200};
  uint8_t datas[List_Elements][MAX_ELEM_SIZE] = {"Pedro,103457", "Carlos,103187", "Americo,45412", "João,87412", "Romario,45872", "JOSE,541256"};
  for (int k = 0; k < List_Elements; k++) {
        MyDLLInsert(&dll, keys[k], datas[k]); // Add nodes to the DLL
    }
  printf("\nComplete List: \n");
  MyDLLPrint(&dll);
  
  MyDLL* NextNode = MyDLLFindNext(&dll, 1078);
  printf("Next element of key 1078 has the key -> %d and the following data ->  %s\n",NextNode -> key, NextNode -> data);
  MyDLL* PreviousNode = MyDLLFindPrevious(&dll, 1078);
  printf("Previous element of key 1078 has the key -> %d and the following data ->  %s\n",PreviousNode -> key, PreviousNode -> data);
  
}

void Teste7(){
  #define List_Elements 6
  DLL_List dll;
  MyDLLInit(&dll); // Initialize the DLL 
  uint16_t keys[List_Elements] = {100, 105, 1078, 102, 154, 200};
  uint8_t datas[List_Elements][MAX_ELEM_SIZE] = {"Pedro,103457", "Carlos,103187", "Americo,45412", "João,87412", "Romario,45872", "JOSE,541256"};
  for (int k = 0; k < List_Elements; k++) {
        MyDLLInsert(&dll, keys[k], datas[k]); // Add nodes to the DLL
    }
  printf("\nBefore sort: \n");
  MyDLLPrint(&dll);
  MyDLLSortAscending(&dll);
  printf("\nSort ascending: \n");
  MyDLLPrint(&dll);
  MyDLLSortDescending(&dll);
  printf("\nSort descending: \n");
  MyDLLPrint(&dll);
}
