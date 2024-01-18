#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar as linhas em que a palavra aparece na lista
typedef struct linhas {
    int linha;
    struct linhas *proximo;
    int existeProximo;
} Linhas;

// Estrutura para representar as informações sobre a palavra na lista
typedef struct lista {
    int numLinhas;
    Linhas *linhas;
    char *palavra;
    struct lista *proximo;
    int existeProximo;
} Lista;

// Estrutura que contém a lista
typedef struct {
    Lista *lista;
} Inicio;

// Inicializa a estrutura Inicio
void ini(Inicio *atual) {
    atual->lista = (Lista *)malloc(sizeof(Lista));
}

// Cria um novo Nó na lista e zera os valores
void createList(Lista *atual, Lista *substituto) {
    atual->proximo = (Lista *)malloc(sizeof(Lista));
    atual->existeProximo = 1;
    atual = atual->proximo;
    atual->linhas = (Linhas *)malloc(sizeof(Linhas));
    atual->linhas->existeProximo = 0;
    atual->existeProximo = 0;
    if (substituto) {
        atual->proximo = substituto;
        atual->existeProximo = 1;
    }
    atual->palavra = NULL;
    atual->numLinhas = 0;
}

// Insere uma linha no Nó da lista
void insertLine(Linhas *linhaAtual, int lineNum) {
    int noRepeat = 1;
    while (linhaAtual->existeProximo == 1) {
        linhaAtual = linhaAtual->proximo;
        if (linhaAtual->linha == lineNum) {
            noRepeat = 0;
        }
    }
    if (noRepeat) {
        linhaAtual->existeProximo = 1;
        linhaAtual->proximo = (Linhas *)malloc(sizeof(Linhas));
        linhaAtual = linhaAtual->proximo;
        linhaAtual->linha = lineNum;
        linhaAtual->existeProximo = 0;
    }
}

// Insere uma palavra na lista
void InsertOnList(Lista *atual, char palavra[], int lineNum) {
    int doit = 1;
    while (doit) {
        if (atual->existeProximo == 0) {
            createList(atual, NULL);
            doit = 0;
        } else {
            if (strcmp(atual->proximo->palavra, palavra) > 0) {
                createList(atual, atual->proximo);
                doit = 0;
            } else {
                if (strcmp(atual->proximo->palavra, palavra) == 0) {
                    doit = 0;
                } else {
                    atual = atual->proximo;
                }
            }
        }
    }
    int size = strlen(palavra) + 1;
    atual = atual->proximo;
    if (atual->palavra == NULL) {
        atual->palavra = (char *)malloc(size * sizeof(char));
        strcpy(atual->palavra, palavra);
    }
    atual->numLinhas++;
    insertLine(atual->linhas, lineNum);
}
