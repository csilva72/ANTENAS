//
// Created by Carlos Silva on 17/05/2025.
//

#ifndef FUNCOES_H
#define FUNCOES_H

//estrutra com as adjacencias do mapaVertices
typedef struct mapaAdjacencias {
    struct mapaVertices* destino;
    struct mapaAdjacencias* next;
} mapaAdjacencias;

//estrutura com os vértices
typedef struct mapaVertices {
    int x, y;
    char valor;
    mapaAdjacencias* adjacentes;
    struct mapaVertices* next;
} mapaVertices;

//cria e inicializa um novo vértice
mapaVertices* criarVertice(int x, int y, char valor);

//insere um vértice na lista ligada do grafo
mapaVertices* inserirVertice(mapaVertices* head, int x, int y, char valor);

//procura um vértice pelas coordenadas
mapaVertices* procurarVertice(mapaVertices* head, int x, int y);

//cria um grafo 12x12 com todos os vértices com valor '.'
mapaVertices* criarGrafo(void);

//insere uma antena numa posição específica
void inserirAntena(mapaVertices* head, int x, int y, char tipo);

//remove uma antena numa posição específica
void removerAntena(mapaVertices* head, int x, int y);

//gera nefastos '#' entre antenas iguais (no meio)
void criarNefasto(mapaVertices* head);

//lê o grafo do ficheiro
mapaVertices* lerFicheiro(void);

//grava o grafo atual no ficheiro
void escreverFicheiro(mapaVertices* head);

//procura um tipo de antena e devolve as coordenandas de onde está
void procurarAntenas(mapaVertices* head, char tipo);


#endif