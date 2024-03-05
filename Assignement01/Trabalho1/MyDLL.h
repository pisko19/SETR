#ifndef MyDLL.h
#define MyDLL.h

#include <stdint.h>

typedef struct MyDLL{
       
   uint16_t key;
   unsigned char* data;
   struct MyDLL* previous;
   struct MyDLL* next;
     
}
   
typedef struct DLL_List{
     
   struct MyDLL* head;
   struct MyDLL* tail;
   unsigned Num_Elements;
   unsigned Size_Elements;

   bool MyDLLInit();
   bool MyDLLInsert();
   bool MyDLLRemove();
   MyDLL* MyDLLFind();
   


}

#endif

