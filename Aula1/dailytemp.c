#include <stdio.h>

typedef struct dailytemp
{
    int position;
    int tempVect[24];
} dailytemp;

void dtInit(int *vect)
{
    memset (vect, 0,24*sizeof(int));
}

void dtAdd(int* vect, int temp)
{
    if(temp <= 50 && temp >= -50 )
        {
            vect->tempVect[vect->position] = temp;
            vect->position++;
        }
}


