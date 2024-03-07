#include <stdio.h>
#include "MyDLL.h"

int main() {
    DLL_List dll;
    MyDLLInit(&dll); // Inicializa a DLL

    // Adiciona o primeiro nó com um nome e uma morada
    uint16_t key1 = 104;
    uint8_t data1[MAX_ELEM_SIZE] = "Pedro Afonso, Tarei";
    MyDLLAdd(&dll, key1, data1);

    // Adiciona o segundo nó com um nome e uma morada
    uint16_t key2 = 103;
    uint8_t data2[MAX_ELEM_SIZE] = "Carlos Teixeira", "Souto"; // não funciona, so como está em cima
    MyDLLAdd(&dll, key2, data2);

    // Imprime os dados da lista
    MyDLLPrint(&dll);

    return 0;
}
