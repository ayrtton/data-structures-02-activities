#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include "Grafo.h"

int existe(char *vet, char ch)
{
    int i;
    char aux;

    for(i=0; vet[i]!='\0'; i++)
        if(vet[i] == ch)
            return i;
    return -1;
}

int conversor(char ch[], int tam)
{
    int i, j;
    int x;

    if(tam==1)
        x = ch[0] - '0';
    else
    {
        x = 0;
        j = 1;
        for(i=tam-1; i>=0; i--)
        {
            x += (ch[i] - '0') * j;
            j *= 10;
        }
    }

    return x;
}

int main()
{
    setlocale(LC_ALL, "");

    FILE *fp;
    char ch;
    char arquivo[12], linha[10], vertices[10], peso_ch[2];
    int i = 0, aux, tam, origem, destino, peso_int;
    Grafo *gr;
    int *ant, *dist;

    printf("Arquivo: ");
    gets(arquivo);
    if((fp = fopen(arquivo, "r")) == NULL)
    {
        printf("Arquivo inexistente.");
        exit(1);
    }

    while((ch = fgetc(fp))!=EOF)
    {
        ch = toupper(ch);
        if(existe(vertices, ch) == -1 && ch >= (char)65 && ch <= (char)90)
        {
            vertices[i] = ch;
            i++;
        }
    }
    vertices[i] = '\0';

    tam = strlen(vertices);
    gr = cria_grafo(tam, tam, 1);
    ant = (int*)malloc(tam * sizeof(int));
    dist = (int*)malloc(tam * sizeof(int));

    rewind(fp);
    while(fgets(linha, sizeof linha, fp)!=NULL)
    {
        peso_ch[0] = linha[4];
        if(isdigit(linha[5]))
        {
            peso_ch[1] = linha[5];
            peso_ch[2] = '\0';
        }
        else
            peso_ch[1] = '\0';

        peso_int = conversor(peso_ch, strlen(peso_ch));

        origem = toupper(linha[0]) - 'A';
        destino = toupper(linha[2]) - 'A';

        insere_aresta(gr, origem, destino, 1, peso_int);
    }
    imprime_grafo(gr);

    while(1)
    {
        printf("Entre com o vértice: ");
        scanf(" %c", &ch);
        aux = ch - 'A';
        if(aux < 0 || aux > gr->vertices-1)
            printf("Vértice inválido");
        else
        {
            menor_caminho(gr, aux, ant, dist);
            for(i=0; i<gr->vertices; i++)
                printf("%c -> %c = %d\n", (char)aux+65, (char)i+65, dist[i]);
            break;
        }
        putchar('\n');
    }

    free(ant);
    free(dist);
    libera_grafo(gr);
    fclose(fp);
}
