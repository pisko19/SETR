#ifndef MyDLL.h
#define MyDLL.h
#define MAX_ELEM_SIZE 100
#define MAX_LIST_SIZE 50

#include <stdint.h>

typedef struct MyDLL{
       
   uint16_t key;
   uint8_t data[MAX_ELEM_SIZE];
   struct MyDLL* Next;
   struct MyDLL* Previous;
     
}
   
typedef struct DLL_List{
   
   MyDLL nodes[MAX_LIST_SIZE];.
   MyDLL* Head;
   MyDLL* Tail;
   
   //Podemos usar um array para os ponteiros

}

bool 

#endif

