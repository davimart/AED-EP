#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar as linhas em que a palavra aparece
typedef struct linha {
    int linha;
    struct linha *proximo;
    int existeProximo;
} LinhasArvore;

// Estrutura para representar as informações sobre a palavra
typedef struct no {
    int numLinhas;
    LinhasArvore *linhas;
    char *palavra;
    struct no *esq;
    struct no *dir;
} No;

// Estrutura para representar a base da árvore binária
typedef struct arvore {
    No *raiz;
} Arvore;

// Função para criar um novo Nó e retornar seu ponteiro
No *criarNo(char *palavra) {
    No *novo = (No *)malloc(sizeof(No));
    novo->numLinhas = 0;
    novo->linhas = (LinhasArvore *)malloc(sizeof(LinhasArvore));
    int size = strlen(palavra) + 1;
    novo->palavra = (char *)malloc(size * sizeof(char));
    strcpy(novo->palavra, palavra);
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

// Função para inserir uma linha no Nó
void insertLineArvore(LinhasArvore *linhaAtual, int lineNum) {
    int noRepeat = 1;
    while (linhaAtual->existeProximo == 1) {
        linhaAtual = linhaAtual->proximo;
        if (linhaAtual->linha == lineNum) {
            noRepeat = 0;
        }
    }
    if (noRepeat) {
        linhaAtual->existeProximo = 1;
        linhaAtual->proximo = (LinhasArvore *)malloc(sizeof(LinhasArvore));
        linhaAtual = linhaAtual->proximo;
        linhaAtual->linha = lineNum;
        linhaAtual->existeProximo = 0;
    }
}

// Função para inserir uma palavra nova (recursão)
void insereOrd(No *raiz, char *palavra, int linha) {
    if (strcmp(raiz->palavra, palavra) == 0) {
        raiz->numLinhas++;
        insertLineArvore(raiz->linhas, linha);
    } else {
        if (strcmp(raiz->palavra, palavra) > 0) {
            if (raiz->esq) {
                insereOrd(raiz->esq, palavra, linha);
            } else {
                raiz->esq = criarNo(palavra);
                raiz->esq->numLinhas++;
                insertLineArvore(raiz->esq->linhas, linha);
            }
        } else {
            if (raiz->dir) {
                insereOrd(raiz->dir, palavra, linha);
            } else {
                raiz->dir = criarNo(palavra);
                raiz->dir->numLinhas++;
                insertLineArvore(raiz->dir->linhas, linha);
            }
        }
    }
}

// Função para inserir uma palavra nova
void insere_ord(Arvore *raiz, char *palavra, int linha) {
    if (raiz->raiz) {
        insereOrd(raiz->raiz, palavra, linha);
    } else {
        raiz->raiz = criarNo(palavra);
        insertLineArvore(raiz->raiz->linhas, linha);
    }
}

// Função para buscar por uma palavra
No *busca_bin(No *raiz, char *palavra) {
    if (raiz) {
        if (strcmp(raiz->palavra, palavra) == 0) {
            return raiz;
        }
        if (strcmp(raiz->palavra, palavra) > 0) {
            return busca_bin(raiz->esq, palavra);
        } else {
            return busca_bin(raiz->dir, palavra);
        }
    } else {
        return NULL;
    }
}

// Função para imprimir o conteúdo da árvore (apenas para debug)
void printArvore(No *raiz) {
    if (raiz->esq) {
        printArvore(raiz->esq);
    }
    if (strlen(raiz->palavra) < 8) {
        printf("%s        %i        ", raiz->palavra, raiz->numLinhas);
    } else {
        printf("%s    %i        ", raiz->palavra, raiz->numLinhas);
    }
    LinhasArvore *linAtual = raiz->linhas;
    while (linAtual->existeProximo == 1) {
        linAtual = linAtual->proximo;
        printf("%i, ", linAtual->linha);
    }
    printf("\n");
    if (raiz->dir) {
        printArvore(raiz->dir);
    }
}
