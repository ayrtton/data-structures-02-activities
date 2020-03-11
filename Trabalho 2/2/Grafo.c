#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

//fonte: https://www.youtube.com/watch?v=gJvSmrxekDo&list=PL8iN9FQ7_jt4oQHq1TSeMgvVdolJvYsLO

Grafo *cria_grafo(int vertices, int grau_max, int ponderado)
{
    Grafo *gr = (Grafo*)malloc(sizeof(Grafo));

    if(gr != NULL)
    {
        int i;
        gr->vertices = vertices;
        gr->grau_max = grau_max;
        gr->ponderado = (ponderado != 0) ? 1:0;
        gr->grau = (int*)calloc(vertices, sizeof(int));
        gr->arestas = (int**)malloc(vertices * sizeof(int*));
        for(i=0; i<vertices; i++)
            gr->arestas[i] = (int*)malloc(grau_max * sizeof(int));
        if(gr->ponderado)
        {
            gr->pesos = (float**)malloc(vertices * sizeof(float*));
            for(i=0; i<vertices; i++)
                gr->pesos[i] = (float*)malloc(grau_max * sizeof(float));
        }
    }

    return gr;
}

void libera_grafo(Grafo* gr)
{
    if(gr != NULL)
    {
        int i;
        for(i=0; i<gr->vertices; i++)
            free(gr->arestas[i]);
        free(gr->arestas);

        if(gr->ponderado)
        {
            for(i=0; i<gr->vertices; i++)
                free(gr->pesos[i]);
            free(gr->pesos);
        }
        free(gr->grau);
        free(gr);
    }
}

int insere_aresta(Grafo* gr, int orig, int dest, int digrafo, int peso)
{
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->vertices)
        return 0;
    if(dest < 0 || dest >= gr->vertices)
        return 0;

    gr->arestas[orig][gr->grau[orig]] = dest;
    if(gr->ponderado)
        gr->pesos[orig][gr->grau[orig]] = peso;
    gr->grau[orig]++;

    if(digrafo == 0)
        insere_aresta(gr, dest, orig, 1, peso);

    return 1;
}

int remove_aresta(Grafo* gr, int orig, int dest, int digrafo)
{
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->vertices)
        return 0;
    if(dest < 0 || dest >= gr->vertices)
        return 0;

    int i = 0;
    while(i<gr->grau[orig] && gr->arestas[orig][i] != dest)
        i++;
    if(i == gr->grau[orig])
        return 0;
    gr->grau[orig]--;
    gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]];
    if(gr->ponderado)
        gr->pesos[orig][i] = gr->pesos[orig][gr->grau[orig]];
    if(digrafo == 0)
        remove_aresta(gr, dest, orig, 1);

    return 1;
}

void imprime_grafo(Grafo* gr)
{
    int i, j;

    for(i=0; i<gr->vertices; i++)
    {
        printf("Vertice %c: ", (char)i+65);
        for(j=0; j<gr->grau[i]; j++)
        {
            printf("%c(%d) ", (char)gr->arestas[i][j]+65, gr->pesos[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}


int menor_distancia(int *dist, int *visitado, int nv)
{
    int i, menor = -1, primeiro = 1;

    for(i=0; i<nv; i++)
    {
        if(dist[i] >= 0 && visitado[i] == 0)
        {
            if(primeiro)
            {
                menor = i;
                primeiro = 0;
            }
            else
            {
                if(dist[menor] > dist[i])
                    menor = i;
            }
        }
    }
    return menor;
}

void menor_caminho(Grafo* gr, int ini, int *ant, int *dist)
{
    int i, cont, nv, ind, *visitado, u;
    cont = nv = gr->vertices;
    visitado = (int*)malloc(nv * sizeof(int));
    for(i=0; i<nv; i++)
    {
        ant[i] = -1;
        dist[i] = -1;
        visitado[i] = 0;
    }
    dist[ini] = 0;
    while(cont > 0)
    {
        u = menor_distancia(dist, visitado, nv);
        if(u == -1)
            break;
        visitado[u] = 1;
        cont--;
        for(i=0; i<gr->grau[u]; i++)
        {
            ind = gr->arestas[u][i];
            if(dist[ind] < 0)
            {
                dist[ind] = dist[u] + gr->pesos[u][i];
                ant[ind] = u;
            }
            else
            {
                if(dist[ind] > dist[u] + 1)
                {
                    dist[ind] = dist[u] + gr->pesos[u][i];
                    ant[ind] = u;
                }
            }
        }
    }
    free(visitado);
}
