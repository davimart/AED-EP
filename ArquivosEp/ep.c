/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2023                           **/
/**   Turma 94 - Prof. Flávio Luiz Coutinho                         **/
/**                                                                 **/
/**   Exercício-Programa                                            **/
/**                                                                 **/
/**  <Gabriel Bernardini Schimidt>                <12873188>        **/
/**  <Fernando Webes Soares Brandão>              <13672940>        **/
/**  <Davi Martins>                               <10337787>        **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/time.h>  // Incluído para usar gettimeofday
#include "funcoes.h"
#include <locale.h>    // Incluído para usar setlocale
#include <string.h>    // Incluído para usar strlen

// Estruturas e funções adicionadas para medição de tempo
double getMilliseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000.0;
}

typedef struct {
    double cargaEConstrucao; // Tempo para carregar o arquivo e construir o índice
    double busca;            // Tempo de busca
} Tempos;

// Função para realizar a busca e medir o tempo
void realizarBusca(Texto texto, Inicio *lista, Arvore *raiz, char palavra[], int Lista, Tempos *tempos) {
    // Medir tempo de busca
    double tempoInicio = getMilliseconds();
    
    busca(texto, lista->lista, raiz->raiz, palavra, Lista);

    double tempoFim = getMilliseconds();
    tempos->busca = tempoFim - tempoInicio;
    printf("Tempo de busca: %.2f ms\n", tempos->busca);
}

// Função para remover pontuação
void removePontuacao(char *str) {
    int count = 0;
    for (int i = 0; str[i]; i++)
        if (str[i] != '.' && str[i] != ',' && str[i] != ';' && str[i] != '!' && str[i] != '?')
            str[count++] = str[i];
    str[count] = '\0';
}

int main(int argc, char **argv) {
    setlocale(LC_ALL, ".UTF8");  // Adicionado para lidar com acentuação

    int Lista = 0;
    if (argc < 3) {
        printf("too few arguments\n");
        return 1;
    } else if (argc > 3) {
        printf("too many arguments\n");
        return 1;
    }

    if (strcmp(argv[2], "arvore") == 0 || strcmp(argv[2], "lista") == 0) {
        printf("Tipo de indice: '%s'\n", argv[2]);
        if (strcmp(argv[2], "lista") == 0) {
            Lista = 1;
        }
    } else {
        printf("Tipo de indice '%s' nao reconhecido!\n", argv[2]);
        return 1;
    }

    Inicio lista;
    ini(&lista);

    Arvore *raiz = (Arvore *)malloc(sizeof(Arvore));
    raiz->raiz = NULL;

    FILE *arq;
    arq = fopen(argv[1], "r");
    if (arq == NULL) {
        printf("Arquivo '%s' nao encontrado.\n", argv[1]);
        return 1;
    }

    printf("Arquivo texto: '%s'\n", argv[1]);

    Texto texto;
    Tempos tempos; // Estrutura para armazenar tempos

    // Medir tempo para carregar o arquivo e construir o índice
    double tempoInicio = getMilliseconds();
    int lineNum = getText(&texto, arq);
    fclose(arq);

    for (int i = 0; i < lineNum; i++) {
        linhaEmLista(texto.linha[i], &lista, raiz, i, Lista);
    }
    double tempoFim = getMilliseconds();
    tempos.cargaEConstrucao = tempoFim - tempoInicio;

    printf("Numero de linhas no arquivo: %i\n", lineNum);
    printf("Tempo para carregar o arquivo e construir o indice: %.2f ms\n", tempos.cargaEConstrucao);

    while (1) {
        printf(">");
        char action[10];
        char word[50];
        scanf("%s", action);

	    scanf("%s", &word);
		for(int i=0; action[i]; i++){
			action[i] = (char) tolower((int)action[i]);
		}
		for(int i=0; word[i]; i++){
			word[i] = tolower(word[i]);
		}

        removePontuacao(action); 
        removePontuacao(word);    

        if (!strcmp(action, "busca")) {
            realizarBusca(texto, &lista, raiz, word, Lista, &tempos);
        } else if (!strcmp(action, "fim")) {
            break;
        } else {
            printf("Opcao invalida!\n");
        }
    }

    return 0;
}
