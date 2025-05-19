//
// Created by Carlos Silva on 17/05/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

#define CAMINHO_FICHEIRO "/Users/csilva/Desktop/IPCA/LESI/EDA/TP1_V5_GRAFOS/mapa.txt"


//cria e inicializa um novo vértice do grafo com as coordenadas e o valor fornecido.
mapaVertices* criarVertice(int x, int y, char valor) {
    mapaVertices* novo = (mapaVertices*)malloc(sizeof(mapaVertices));
    if (!novo) return NULL;
    novo->x = x;
    novo->y = y;
    novo->valor = valor;
    novo->adjacentes = NULL;
    novo->next = NULL;
    return novo;
}


//insere um novo vértice no início da lista ligada do grafo
mapaVertices* inserirVertice(mapaVertices* head, int x, int y, char valor) {
    mapaVertices* novo = criarVertice(x, y, valor);
    if (!novo) return head;
    novo->next = head;
    return novo;
}

//procura um vértice específico pelas coordenadas (x, y)
mapaVertices* procurarVertice(mapaVertices* head, int x, int y) {
    while (head) {
        if (head->x == x && head->y == y) return head;
        head = head->next;
    }
    return NULL;
}

//cria um grafo 12x12 preenchido com o valor '.' em todas as posições.
mapaVertices* criarGrafo() {
    mapaVertices* head = NULL;
    for (int i = 11; i >= 0; i--) {
        for (int j = 11; j >= 0; j--) {
            head = inserirVertice(head, i, j, '.');
        }
    }
    return head;
}

//insere uma antena no vértice correspondente às coordenadas dadas
void inserirAntena(mapaVertices* head, int x, int y, char tipo) {
    mapaVertices* v = procurarVertice(head, x, y);
    if (v) v->valor = tipo;
}

//remove uma antena
void removerAntena(mapaVertices* head, int x, int y) {
    mapaVertices* v = procurarVertice(head, x, y);
    if (v && v->valor != '.') {
        v->valor = '.';  // Marca como vazio
    }
}

//cria nefasto no meio de um par de antenas
void criarNefasto(mapaVertices* head) {
    for (mapaVertices* a = head; a != NULL; a = a->next) {
        if (a->valor >= 'A' && a->valor <= 'Z') {
            for (mapaVertices* b = a->next; b != NULL; b = b->next) {
                if (b->valor == a->valor) {
                    int mx = (a->x + b->x) / 2;
                    int my = (a->y + b->y) / 2;
                    mapaVertices* meio = procurarVertice(head, mx, my);
                    if (meio && meio->valor == '.') {
                        meio->valor = '#';
                    }
                }
            }
        }
    }
}

//lê o ficheiro de texto e carrega os vértices com os valores que estão dentro do ficheiro
mapaVertices* lerFicheiro() {
    FILE* f = fopen(CAMINHO_FICHEIRO, "r");
    mapaVertices* mapa = criarGrafo();
    if (!f) return mapa;

    char linha[20];  // aceita até 12 caracteres + margem
    int x = 0;

    while (fgets(linha, sizeof(linha), f) && x < 12) {
        for (int y = 0; y < 12 && linha[y] != '\n' && linha[y] != '\0'; y++) {
            char c = linha[y];
            if (c != '.') {
                inserirAntena(mapa, x, y, c);
            }
        }
        x++;
    }

    fclose(f);
    return mapa;
}


//escreve os vértices do grafo no ficheiro em formato matriz de 12 por 12
void escreverFicheiro(mapaVertices* head) {
    FILE* f = fopen(CAMINHO_FICHEIRO, "w");
    if (!f) return;

    // Inicializa matriz com '.'
    char matriz[12][12];
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 12; j++)
            matriz[i][j] = '.';

    //preenche a matriz com os valores do grafo
    while (head) {
        matriz[head->x][head->y] = head->valor;
        head = head->next;
    }

    //escreve a matriz no ficheiro
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            fputc(matriz[i][j], f);
        }
        fputc('\n', f); // nova linha ao fim de cada linha da matriz
    }

    fclose(f);
}


//procura uma determinada antena e devolve as coordenandas
void procurarAntenas(mapaVertices* head, char tipo) {
    printf("Antenas do tipo '%c' encontradas nas posições:\n", tipo);
    int encontrou = 0;
    while (head) {
        if (head->valor == tipo) {
            printf("  - Linha: %d, Coluna: %d\n", head->x, head->y);
            encontrou = 1;
        }
        head = head->next;
    }
    if (!encontrou) {
        printf("Nenhuma antena '%c' encontrada.\n", tipo);
    }
}


