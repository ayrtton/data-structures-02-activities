#include <stdio.h>
#include <stdlib.h>

#define N 0.01

float BuscaBinaria(int n)
{
    float inf = 0, sup = n - N, meio, busca = -1;

    while(inf <= sup)
    {
        meio = (inf + sup) / 2;
        if((meio + 1) * (meio + 1) == n)
        {
            busca = meio;
            inf = sup + 1;
        }
        else if((meio + 1) * (meio + 1) < n)
            inf = meio + N;
        else if((meio + 1) * (meio + 1) > n)
        {
            sup = meio - N;
            busca = meio - N;
        }
    }
    return busca + 1;
}

int main()
{
    int x;
    float j;

    while(1)
    {
        printf("Entre com o valor[negativo para sair]: ");
        scanf("%d", &x);
        if(x < 0)
            break;
        j = BuscaBinaria(x);
        printf("Raiz = %.2f\n\n", j);
    }
}
