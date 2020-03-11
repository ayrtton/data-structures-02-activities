#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter(); // fonte:
double GetCounter(); // https://www.dropbox.com/s/6nrg6v06xesxs8e/medeRuntime.c
void MinMax1(long int *vet, long int *min, long int *max, long int tam, long int *comp, double *tempo);
void MinMax2(long int *vet, long int *min, long int *max, long int tam, long int *comp, double *tempo);
void MinMax3(long int *vet, long int *min, long int *max, long int tam, long int *comp, double *tempo);
void preenche_crescente(long int *vet, long int tam);
void preenche_decrescente(long int *vet, long int tam);
void preenche_aleatorio(long int *vet, long int tam);

int main()
{
    setlocale(LC_ALL, "");

    int i, k;

    long int *sequencia[120];
    long int comparacoes[120];
    long int j, min, max, soma;

    double soma_tempo, tempo[120];

    j = 10000;
    for(i=0; i<120; i++)
    {
        sequencia[i] = (long int*)calloc(j, sizeof(long int));

        if(i % 12 == 0)
            preenche_crescente(sequencia[i], j);
        else if((i - 1) % 12 == 0)
            preenche_decrescente(sequencia[i], j);
        else
            preenche_aleatorio(sequencia[i], j);

        if((i + 1) % 12 == 0)
            j += 10000;
    }

    printf("Algoritmo 1:\n");
    printf("Crescente:\n");
    for(i=0, j=10000; i<120; i+=12, j+=10000)
    {
        MinMax1(sequencia[i], &min, &max, j, &comparacoes[i], &tempo[i]);
        printf("%ld -> %ld comparações | %.2f ms\n", j, comparacoes[i], tempo[i]);
    }
    printf("\nDecrescente:\n");
    for(i=1, j=10000; i<120; i+=12, j+=10000)
    {
        MinMax1(sequencia[i], &min, &max, j, &comparacoes[i], &tempo[i]);
        printf("%ld -> %ld comparações | %.2f ms\n", j, comparacoes[i], tempo[i]);
    }
    printf("\nAleatório:\n");
    for(i=2, j=10000; i<120; i+=12, j+=10000)
    {
        k = i;
        soma = soma_tempo = 0;
        while(k%12 != 0)
        {
            MinMax1(sequencia[k], &min, &max, j, &comparacoes[k], &tempo[k]);
            soma += comparacoes[k];
            soma_tempo += tempo[k];
            k++;
        }
        printf("%ld -> %ld comparações | %.2f ms\n", j, soma/10, soma_tempo/10);
    }

    printf("\n-------------------------------------\n");
    printf("Algoritmo 2:\n");
    printf("Crescente:\n");
    for(i=0, j=10000; i<120; i+=12, j+=10000)
    {
        MinMax2(sequencia[i], &min, &max, j, &comparacoes[i], &tempo[i]);
        printf("%ld -> %ld comparações | %.2f ms\n", j, comparacoes[i], tempo[i]);
    }
    printf("\nDecrescente:\n");
    for(i=1, j=10000; i<120; i+=12, j+=10000)
    {
        MinMax2(sequencia[i], &min, &max, j, &comparacoes[i], &tempo[i]);
        printf("%ld -> %ld comparações | %.2f ms\n", j, comparacoes[i], tempo[i]);
    }
    printf("\nAleatório:\n");
    for(i=2, j=10000; i<120; i+=12, j+=10000)
    {
        k = i;
        soma = soma_tempo = 0;
        while(k%12 != 0)
        {
            MinMax2(sequencia[k], &min, &max, j, &comparacoes[k], &tempo[k]);
            soma += comparacoes[k];
            soma_tempo += tempo[k];
            k++;
        }
        printf("%ld -> %ld comparações | %.2f ms\n", j, soma/10, soma_tempo/10);
    }

    printf("\n-------------------------------------\n");
    printf("Algoritmo 3:\n");
    printf("Crescente:\n");
    for(i=0, j=10000; i<120; i+=12, j+=10000)
    {
        MinMax3(sequencia[i], &min, &max, j, &comparacoes[i], &tempo[i]);
        printf("%ld -> %ld comparações | %.2f ms\n", j, comparacoes[i], tempo[i]);
    }
    printf("\nDecrescente:\n");
    for(i=1, j=10000; i<120; i+=12, j+=10000)
    {
        MinMax3(sequencia[i], &min, &max, j, &comparacoes[i], &tempo[i]);
        printf("%ld -> %ld comparações | %.2f ms\n", j, comparacoes[i], tempo[i]);
    }
    printf("\nAleatório:\n");
    for(i=2, j=10000; i<120; i+=12, j+=10000)
    {
        k = i;
        soma = soma_tempo = 0;
        while(k%12 != 0)
        {
            MinMax3(sequencia[k], &min, &max, j, &comparacoes[k], &tempo[k]);
            soma += comparacoes[k];
            soma_tempo += tempo[k];
            k++;
        }
        printf("%ld -> %ld comparações | %.2f ms\n", j, soma/10, soma_tempo/10);
    }

    for(i=0; i<120; i++)
        free(sequencia[i]);
}

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        printf("QueryPerformanceFrequency Failed.\n");
    PCFreq = (double)(li.QuadPart) / 1000.0;
    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return (double)(li.QuadPart - CounterStart) / PCFreq;
}

void preenche_crescente(long int *vet, long int tam)
{
    long int i;

    for(i=0; i<tam; i++)
        vet[i] = i + 1;
}

void preenche_decrescente(long int *vet, long int tam)
{
    long int i;

    for(i=0; i<tam; i++)
        vet[i] = tam - i;
}

void preenche_aleatorio(long int *vet, long int tam)
{
    long int i, x, aux = 0;

    srand((long)time(0));

    x = rand() % tam;
    for(i=0; i<tam; i++)
    {
        while(vet[x] != 0)
            x = (rand() % tam) + aux;
        vet[x] = i+1;
        if(i > 0 && i % RAND_MAX == 0)
            aux = tam - RAND_MAX * (i/RAND_MAX);
    }
}

void MinMax1(long int *vet, long int *min, long int *max, long int tam, long int *comp, double *tempo)
{
    long int i;

    *min = *max = vet[0];
    *comp = 0;
    *tempo = 0.0000000;
    StartCounter();

    for(i=1; i<tam; i++)
    {
        (*comp)++;
        if(vet[i] > *max)
            *max = vet[i];
        (*comp)++;
        if(vet[i] < *min)
            *min = vet[i];
    }

    *tempo = GetCounter();
}

void MinMax2(long int *vet, long int *min, long int *max, long int tam, long int *comp, double *tempo)
{
    long int i;

    *min = *max = vet[0];
    *comp = 0;
    *tempo = 0.0000000;
    StartCounter();

    for(i=1; i<tam; i++)
    {
        (*comp)++;
        if(vet[i] > *max)
            *max = vet[i];
        else
        {
            (*comp)++;
            if(vet[i] < *min)
                *min = vet[i];
        }
    }

    *tempo = GetCounter();
}

void MinMax3(long int *vet, long int *min, long int *max, long int tam, long int *comp, double *tempo)
{
    long int i, cont;

    *comp = 0;
    *tempo = 0.0000000;
    StartCounter();

    if (tam % 2 > 0)
    {
        vet[tam] = vet[tam - 1];
        cont = tam;
    }
    else
        cont = tam - 1;

    (*comp)++;
    if (vet[0] > vet[1])
    {
        *max = vet[0];
        *min = vet[1];
    }
    else
    {
        *max = vet[1];
        *min = vet[0];
    }
    i = 3;

    while (i <= cont)
    {
        (*comp)++;
        if (vet[i - 1] > vet[i])
        {
            (*comp)++;
            if (vet[i - 1] > *max)
                *max = vet[i - 1];
            (*comp)++;
            if (vet[i] < *min)
                *min = vet[i];
        }
        else
        {
            (*comp)++;
            if (vet[i - 1] < *min)
                *min = vet[i - 1];
            (*comp)++;
            if (vet[i] > *max)
                *max = vet[i];
        }
        i += 2;
    }

    *tempo = GetCounter();
}
