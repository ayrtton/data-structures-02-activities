#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

typedef struct grafo
{
    int ponderado, vertices, grau_max;
    int** arestas;
    int** pesos;
    int* grau;
} Grafo;

Grafo* cria_grafo(int vertices, int grau_max, int ponderado);
void libera_grafo(Grafo* gr);
int insere_aresta(Grafo* gr, int orig, int dest, int digrafo, int peso);
int remove_aresta(Grafo* gr, int orig, int dest, int digrafo);
int menor_distancia(int *dist, int *visitado, int nv);
void menor_caminho(Grafo* gr, int ini, int *ant, int *dist);

#endif // GRAFO_H_INCLUDED
