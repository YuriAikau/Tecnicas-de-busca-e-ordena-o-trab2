#include <limits.h>
#include <math.h>
#include "algoritmo.h"


static int compare(const void* item1, const void* item2){
    double i1 = ((Inflacao*)item1)->inflation;
    double i2 = ((Inflacao*)item2)->inflation;

    if(fabs(i1-i2) < 10e-22) return 0;
    return i1 > i2 ? 1 : -1;
}

Lista** inicializa_leitura(FILE* entrada, int v, int e){
    Lista** nos = (Lista**)malloc(v*sizeof(Lista));
    for(int i = 0; i < v; i++) nos[i] = inic_lista();

    int noA, noB;
    double tempo;

    for(int l = 0; l < e; l++){
        fscanf(entrada, " %d %d %lf", &noA, &noB, &tempo);

        Item* aresta = (Item*)malloc(sizeof(Item));
        aresta->id = noB;
        aresta->value = tempo;
        insere_lista(nos[noA], aresta);
    }

    return nos;
}

double** dijkstra(Lista** grafo, VetInt source, int numNos){
    double** matrizTempos = (double**)malloc((source.size)*sizeof(double*));
    for(int count = 0; count < (source.size); count++) matrizTempos[count] = (double*)malloc(numNos*sizeof(double));

    for(int i = 0; i < source.size; i++){
        int indiceSource = source.vector[i];
        for(int j = 0; j < numNos; j++) matrizTempos[i][j] = (double)INT_MAX;
        matrizTempos[i][indiceSource] = 0.0f;

        Item sourceDist;
        id(sourceDist) = indiceSource;
        value(sourceDist) = 0.0f;

        PQueue* priorityQueue = PQ_init(numNos);
        
        PQ_insert(sourceDist, priorityQueue);

        int noAtual;
        double tempDist;
        while(!PQ_empty(priorityQueue)){
            Celula* p;
            Item arestaMin;

            arestaMin = PQ_delmin(priorityQueue);
            noAtual = id((arestaMin));

            for (p = grafo[noAtual]->primeira; p != NULL; p = p->prox){ // Pecorre todos os nós adjacentes
                int idElemento = p->aresta->id;
                double valueElemento = p->aresta->value;

                tempDist = matrizTempos[i][noAtual] + valueElemento;
                if(matrizTempos[i][idElemento] > tempDist){ // Verifica se o tempo até o nó já é irredutível
                    matrizTempos[i][idElemento] = tempDist;
                    if(PQ_contains(idElemento, priorityQueue)){
                        PQ_decrease_key(idElemento, tempDist, priorityQueue);
                    }else{
                        Item tempItem = *p->aresta;
                        tempItem.value = tempDist;
                        PQ_insert(tempItem, priorityQueue);
                    }
                }
            }
        }
        PQ_finish(priorityQueue);
    }
    return matrizTempos;
}

double** rtt(VetInt noA, VetInt noB, double** matriz1, double** matriz2){
    double** temposRtt = (double**)malloc((noA.size)*sizeof(double*));
    for(int i = 0; i < noA.size; i++) temposRtt[i] = (double*)malloc((noB.size)*sizeof(double));

    for(int i = 0; i < noA.size; i++){
        int temp1 = noA.vector[i];
        for(int j = 0; j < noB.size; j++){
            int temp2 = noB.vector[j];
            temposRtt[i][j] = matriz1[i][temp2] + matriz2[j][temp1]; // Tempo de A até B + distância de B até A
        }
    }

    return temposRtt;
}

double** rtt_aproximado(VetInt noA, VetInt noB, VetInt noC, double** matriz1, double** matriz2, double** matriz3){
    double** rttApprox = (double**)malloc((noA.size)*sizeof(double*));
    for(int i = 0; i < noA.size; i++) rttApprox[i] = (double*)malloc((noB.size)*sizeof(double));

    double valorMin = (double)INT_MAX;
    double somaAtual;

    for(int i = 0; i < noA.size; i++){
        int temp1 = noA.vector[i];
        for(int j = 0; j < noB.size; j++){
            int temp2 = noB.vector[j];
            for(int k = 0; k < noC.size; k++){
                int temp3 = noC.vector[k];
                somaAtual = (matriz1[i][temp3] + matriz3[k][temp1]) + (matriz3[k][temp2] + matriz2[j][temp3]); // 
                
                if(somaAtual < valorMin) valorMin = somaAtual;
            }
            rttApprox[i][j] = valorMin;
            valorMin = (double)INT_MAX;
        }
    }

    return rttApprox;
}

Inflacao* cria_vetor_inflacao(double** RTT, double** RTT_APROX, VetInt server, VetInt client){
    int sizeA = server.size;
    int sizeB = client.size;
    int N = 0;

    Inflacao* vetInfl = (Inflacao*)malloc((sizeA*sizeB)*sizeof(Inflacao)); // Para caber todos os elementos dos RTTs

    for(int i = 0; i < sizeA; i++){
        for(int j = 0; j < sizeB; j++){
            vetInfl[N].noServer = server.vector[i];
            vetInfl[N].noClient = client.vector[j];
            vetInfl[N++].inflation = (RTT_APROX[i][j]/RTT[i][j]);
        }
    }

    return vetInfl;
}

void imprime_resultado(FILE* saida ,Inflacao* vetInfl, int tamServer, int tamClient){
    int N = tamServer*tamClient;

    qsort(vetInfl, N, sizeof(Inflacao), compare);

    for(int i = 0; i < N; i++){
        fprintf(saida, "%d %d %.16lf\n", vetInfl[i].noServer, vetInfl[i].noClient, vetInfl[i].inflation);
    }
}

void destroi_grafo(Lista** grafo, int numNos){
    for(int i = 0; i < numNos; i++){
        destroi_lista(grafo[i]);
    }
    free(grafo);
}

void destroi_matriz_dijkstra(double** mat, int tam){
    for(int i = 0; i < tam; i++){
        free(mat[i]);
    }
    free(mat);
}

void destroi_rtts(double** matriz, int tam){
    for(int i = 0; i < tam; i++) free(matriz[i]);
    free(matriz);
}