#ifndef ALGORITMO_H
#define ALGORITMO_H

#include <stdio.h>
#include <stdlib.h>

#include "PQ.h"
#include "linkedlist.h"

typedef struct{
    int* vector;
    int size;
} VetInt;

typedef struct{
    int noServer;
    int noClient;
    double inflation;
} Inflacao;

// Função para a criação da lista de adjacências, sendo um vetor de listas encadeadas
Lista** inicializa_leitura(FILE* entrada, int v, int e);

/*
Função que executa o algoritmo de dijkstra para todos os elementos de um grupo (e.g. servidores),
e armazena esses tempos em uma matriz de double, onde cada posição [m][n] representa o menor tempo do 
elemento contido na posicao [m] no vetor do grupo(source) para cada coluna [n] que representa 1 para 1 o 
indice de todos os nós do grafo.
*/ 
double** dijkstra(Lista** grafo, VetInt source, int numNos);

/*
Função que cria uma matriz de double m x n (m = num. de elementos noA, n = num. de elementos noB) que 
armazena o tempo que leva para chegar de um ponto A até B mais o tempo de B até A, onde cada posição[m][n]
representa o rtt entre o elemento contido na posição [m] do vetor em noA e o elemento contido na posicao [n]
no vetor em noB.
*/
double** rtt(VetInt noA, VetInt noB, double** matriz1, double** matriz2);

/*
Função que cria uma matriz de double m x n (m = num. de elementos noA, n = num. de elementos noB) que 
armazena o menor tempo approximado rtt(A,C) + rtt(C,B) onde C é um monitor, onde cada posição[m][n]
representa o rtt aproximado entre o elemento contido na posição [m] do vetor em noA e o elemento 
contido na posicao [n] no vetor em noB.
*/
double** rtt_aproximado(VetInt noA, VetInt noB, VetInt noC, double** matriz1, double** matriz2, double** matriz3);

/*
Função que cria um vetor do tipo Inflacao que possui as informações necessárias para a impressão, sendo elas:
o nó do servidor,o nó do cliente e a inflação entre eles (rtt_aproximado(A,B)/rtt(A,B)). Portanta esse vetor
possui um tamanho de N (sendo N = num. elementos do server x num. elementos do client) para que possa caber
todos os valores.
*/
Inflacao* cria_vetor_inflacao(double** RTT, double** RTT_APROX, VetInt server, VetInt client);

// Função que organiza o vetor Inflação pelas inflações e imprime todas as posições em um arquivo de saída.
void imprime_resultado(FILE* saida, Inflacao* vetInfl, int tamServer, int tamClient);

// Libera a memória alocada pelo grafo.
void destroi_grafo(Lista** grafo, int numNos);

// Libera a memória alocada pela matriz de dijkstra.
void destroi_matriz_dijkstra(double** mat, int tam);

// Libera a memória alocada pela matriz de rtt e rtt_approximado.
void destroi_rtts(double** matriz, int tam);

#endif //ALGORITMO_H