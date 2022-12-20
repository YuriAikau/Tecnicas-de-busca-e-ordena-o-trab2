#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "algoritmo.h"

int main(int argc, char *argv[]) {
    FILE *entrada;
    entrada = fopen(argv[1],"r");

    int v,e;
    int s,c,m;

    fscanf(entrada, " %d %d ", &v, &e); // Lê os valores dos núm. de nós e arestas
    fscanf(entrada, " %d %d %d ", &s, &c, &m); // Lê os valores dos núm. de servidores, clientes e monitores

    // Inicializa os vetores para armazenar quais elementos pertencem a cada grupo
    VetInt servidores;
    servidores.vector = (int*)malloc(s*sizeof(int));
    servidores.size = s;
    VetInt clientes;
    clientes.vector = (int*)malloc(c*sizeof(int));
    clientes.size = c;
    VetInt monitores;
    monitores.vector = (int*)malloc(m*sizeof(int));
    monitores.size = m;

    // Lê os valores e os armazena sequêncialmente em seus respectivos grupos
    for(int i = 0; i < s; i++) fscanf(entrada,"%d\n", &servidores.vector[i]);
    for(int j = 0; j < c; j++) fscanf(entrada,"%d\n", &clientes.vector[j]);
    for(int k = 0; k < m; k++) fscanf(entrada,"%d\n", &monitores.vector[k]);

    // Inicializa o grafo que lê "e" linhas do arquivo de entrada e armazena no vetor Lista* de "v" linhas
    Lista** grafo = inicializa_leitura(entrada, v, e);

    // Realiza o dijkstra para todos os grupos de interesse
    double** matrizA = dijkstra(grafo, servidores, v);
    double** matrizB = dijkstra(grafo, clientes, v);
    double** matrizC = dijkstra(grafo, monitores, v);

    // Calcula os rtts entre os servidores e clientes
    double** rttDist = rtt(servidores, clientes, matrizA, matrizB);

    // Calcula os rtts_aproximados entre os servidores e clientes, ou seja, eles devem ter um monitor entre seus caminhos
    double** rttApprox = rtt_aproximado(servidores, clientes, monitores, matrizA, matrizB, matrizC);

    // Armazena todos os valores de inflação em um vertor Inflação que possui a informação do cliente, servidor e da inflação propriamente dita
    Inflacao* vetorInflacao = cria_vetor_inflacao(rttDist, rttApprox, servidores, clientes);

    FILE* saida = fopen(argv[2], "w");

    // Imprime os resultados pedidos pelo enunciado
    imprime_resultado(saida, vetorInflacao, servidores.size, clientes.size);

    // Liberação de memória
    fclose(saida);

    destroi_grafo(grafo, v);

    destroi_matriz_dijkstra(matrizA, s);
    destroi_matriz_dijkstra(matrizB, c);
    destroi_matriz_dijkstra(matrizC, m);

    destroi_rtts(rttDist, servidores.size);
    destroi_rtts(rttApprox, servidores.size);

    free(vetorInflacao);

    free(servidores.vector);
    free(clientes.vector);
    free(monitores.vector);

    fclose(entrada);

    return 0;
}