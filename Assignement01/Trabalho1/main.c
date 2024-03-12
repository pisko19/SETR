#include <stdio.h>
#include "MyDLL.h"
#include "Testes.h"


int main() {
    int teste = -1;
    int x;
    while(1){
    if(teste==0)
       break;
    printf("\n\n\nWhat test you want to do ?"
           "\n0 .> EXIT"
           "\n1 -> Test the remove function"
           "\n2 -> Test the limit of the list size"
           "\n3 -> Test the find function"
           "\n4 -> Test the insert function after remove one element"
           "\n5 -> Test any function"
           "\n6 -> Test the find next and previous function"
           "\n7 -> Test the sorting function\n");
    scanf("%d",&teste);
    switch(teste){
        case(0):
        printf("\n\nEND\n\n");
        break;
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
        
      case(6):
        Teste6();
        break;
      
      case(7):
        Teste7();
        break;
        
    
    }
    }
    return 0;
}

