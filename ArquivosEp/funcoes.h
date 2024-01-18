#include <string.h>
#include <time.h>
#include "lista.h"
#include "arvore.h"

// Estrutura para armazenar o texto de forma integral
typedef struct {
    char *linha[10000];
} Texto;

// Função para medir o tempo
float Clock(int reset) {
    static clock_t startTime;
    if (reset) {
        startTime = clock();
    }
    clock_t endTime = clock();
    return 1000 * (((float)(endTime - startTime)) / CLOCKS_PER_SEC);
}

// Função para imprimir tudo o que está armazenado (apenas para debug)
void printAll(Texto *texto, Lista *atual, Arvore *raiz, int lineNum, int Lista) {
    for (int i = 0; i < lineNum; i++) {
        printf("%5i: %s", i, texto->linha[i]);
    }
    if (Lista) {
        printf("\npalavra         aparições    linhas\n\n");
        while (atual->existeProximo == 1) {
            atual = atual->proximo;
            if (strlen(atual->palavra) < 8) {
                printf("%s            %i        ", atual->palavra, atual->numLinhas);
            } else {
                printf("%s        %i        ", atual->palavra, atual->numLinhas);
            }
            Linhas *linAtual = atual->linhas;
            while (linAtual->existeProximo == 1) {
                linAtual = linAtual->proximo;
                printf("%i, ", linAtual->linha);
            }
            printf("\n");
        }
    } else {
        printf("\npalavra         aparições    linhas\n\n");
        printArvore(raiz->raiz);
    }
    printf("\n");
}

// Função para obter as linhas do arquivo externo na memória do programa
int getText(Texto *texto, FILE *arq) {
    char linha[10000];
    int i = 0;
    while (fgets(linha, 10000, arq)) {
        int size = (int)strlen(linha);
        size++;
        texto->linha[i] = (char *)malloc(size * sizeof(char));
        for (int j = 0; j < size; j++) {
            texto->linha[i][j] = linha[j];
        }
        i++;
    }
    return i;
}

// Separação das palavras nas linhas
void linhaEmLista(char linha[], Inicio *lista, Arvore *raiz, int numLinha, int Lista) {
    static int doOnce = 0; // Para uso na lista ligada
    if (!doOnce && Lista) {
        lista->lista->existeProximo = 0;
        doOnce++;
    }
    char palavra[50];
    for (int i = 0; i < 50; i++) {
        palavra[i] = '\0';
    }
    char c = '\0';
    for (int i = 0; c != '\n'; i++) {
        c = linha[i];
        if (c > 64 && c < 91) {
            c += 32;
        }
        if (c == '.' || c == ',' || c == '-' || c == '/' || c == '!' || c == '?' || c == ';' || c == ':' || c == '(' || c == ')' || c == '\0' || c == '\n' || c == '"' || c == '"'|| c == ' ') {
            if (strlen(palavra) < 1) {
                palavra[0] = '\0';
            } else {
                if (Lista) {
                    InsertOnList(lista->lista, palavra, numLinha);
                } else {
                    insere_ord(raiz, palavra, numLinha);
                }
                for (int z = 0; z < 50; z++) {
                    palavra[z] = '\0';
                }
            }
        } else {
            strncat(palavra, &c, 1);
        }
    }
}

// Busca por uma palavra na lista ligada
Lista *buscaLista(Lista *atual, char *palavra) {
    while (atual->existeProximo) {
        atual = atual->proximo;
        if (strcmp(atual->palavra, palavra) == 0) {
            return atual;
        }
    }
    return NULL;
}

// Busca por uma palavra no geral
void busca(Texto texto, Lista *lista, No *raiz, char palavra[], int Lista) {
    float tempo = Clock(1);
    if (Lista) {
        lista = buscaLista(lista, palavra);
        tempo = Clock(0);
        if (lista == NULL) {
            printf("Palavra '%s' não encontrada.\n", palavra);
        } else {
            printf("Existem %i ocorrências da palavra '%s' na(s) seguinte(s) linha(s):\n", lista->numLinhas, palavra);
            Linhas *linha = lista->linhas;
            while (linha->existeProximo) {
                linha = linha->proximo;
                printf("%05i: %s", linha->linha + 1, texto.linha[linha->linha]);
            }
        }
    } else {
        No *no = busca_bin(raiz, palavra);
        tempo = Clock(0);
        if (no == NULL) {
            printf("Palavra '%s' não encontrada.\n", palavra);
        } else {
            printf("Existem %i ocorrências da palavra '%s' na(s) seguinte(s) linha(s):\n", no->numLinhas, palavra);
            LinhasArvore *linha = no->linhas;
            while (linha->existeProximo) {
                linha = linha->proximo;
                printf("%05i: %s", linha->linha + 1, texto.linha[linha->linha]);
            }
        }
    }
    printf("Tempo de busca: %.3f ms\n", tempo);
}
