#include <stdio.h>
#include <string.h>

typedef struct dailytemp
{
    int position;
    int tempVect[24];
} dailytemp;

void dtInit(dailytemp *vect)
{
    memset(vect->tempVect, 0, 24 * sizeof(int));
    vect->position = 0; // Inicializar position para 0
}

void dtAdd(dailytemp *vect, int temp)
{
    if (vect->position < 24) // Verificar se há espaço disponível no vetor
    {
        if (temp <= 50 && temp >= -50)
        {
            vect->tempVect[vect->position] = temp;
            vect->position++;
        }
        else
        {
            printf("Invalid temperature value: %d\n", temp);
        }
    }
    else
    {
        printf("Temperature vector is full.\n");
    }
}

void stStat(dailytemp *vect, int *max, int *min, int *avg)
{
    *max = *min = vect->tempVect[0];
    *avg = 0;
    for (int i = 0; i < vect->position; i++)
    {
        if (*max < vect->tempVect[i])
        {
            *max = vect->tempVect[i];
        }
        if (*min > vect->tempVect[i])
        {
            *min = vect->tempVect[i];
        }
        *avg += vect->tempVect[i];
    }
    *avg = *avg / vect->position;
}

int main()
{
    dailytemp vetor;
    dtInit(&vetor);
    for (int i = 0; i < 10; i++)
    {
        dtAdd(&vetor, i);
    }
    int max, min, avg;
    stStat(&vetor, &max, &min, &avg);
    printf("Temp máxima = %d\nTemp mínima = %d\nTemp média = %d\n", max, min, avg);
    return 0;
}
