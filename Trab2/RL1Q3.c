// Integrantes da equipe: Ana Emilia Lobo e Martfeld Mutim (20241160001) Marcus Vinicius Silva da Fonseca (20241160005) e Roberto Silva Barreto (20241160031)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINES 1000
#define MAX_NUMBERS 1000
#define BUFFER_SIZE 100000

// Estruturas para a Lista Circular e Lista Duplamente Ligada
typedef struct NoCircular {
    float valor;
    struct NoCircular *prox;
} NoCircular;

typedef struct NoDuploInt {
    int chave;
    NoCircular *sublista;
    struct NoDuploInt *prox;
    struct NoDuploInt *ant;
} NoDuploInt;

typedef struct ListaDuplamenteLigadaInt {
    NoDuploInt *inicio;
    NoDuploInt *fim;
} ListaDuplamenteLigadaInt;

// Funções para manipulação da Lista Circular
NoCircular *criarNoCircular(float valor) {
    NoCircular *novo = (NoCircular *)malloc(sizeof(NoCircular));
    novo->valor = valor;
    novo->prox = novo; // Circular
    return novo;
}

void inserirCircular(NoCircular **head, float valor) {
    NoCircular *novo = criarNoCircular(valor);
    if (!*head) {
        *head = novo;
        return;
    }

    NoCircular *atual = *head;
    NoCircular *prev = NULL;

    do {
        if (atual->valor >= valor) break;
        prev = atual;
        atual = atual->prox;
    } while (atual != *head);

    if (!prev) {
        novo->prox = *head;
        NoCircular *ultimo = *head;
        while (ultimo->prox != *head) ultimo = ultimo->prox;
        ultimo->prox = novo;
        *head = novo;
    } else {
        prev->prox = novo;
        novo->prox = atual;
    }
}

// Funções para manipulação da Lista Duplamente Ligada
NoDuploInt *criarNoInt(int chave) {
    NoDuploInt *novo = (NoDuploInt *)malloc(sizeof(NoDuploInt));
    novo->chave = chave;
    novo->sublista = NULL;
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
}

ListaDuplamenteLigadaInt *inicializarListaInt() {
    ListaDuplamenteLigadaInt *lista = (ListaDuplamenteLigadaInt *)malloc(sizeof(ListaDuplamenteLigadaInt));
    lista->inicio = NULL;
    lista->fim = NULL;
    return lista;
}

void inserirOrdenadoInt(ListaDuplamenteLigadaInt *lista, int chave) {
    NoDuploInt *novo = criarNoInt(chave);
    if (!lista->inicio) {
        lista->inicio = lista->fim = novo;
        return;
    }

    NoDuploInt *atual = lista->inicio;
    while (atual && atual->chave < chave) {
        atual = atual->prox;
    }

    if (!atual) {
        lista->fim->prox = novo;
        novo->ant = lista->fim;
        lista->fim = novo;
    } else if (atual == lista->inicio) {
        novo->prox = lista->inicio;
        lista->inicio->ant = novo;
        lista->inicio = novo;
    } else {
        novo->prox = atual;
        novo->ant = atual->ant;
        atual->ant->prox = novo;
        atual->ant = novo;
    }
}

// Funções utilitárias
void conectarLE_LI(ListaDuplamenteLigadaInt *lista, float *numerosLI, int countLI) {
    NoDuploInt *atual = lista->inicio;
    while (atual) {
        int chave = atual->chave;
        for (int i = 0; i < countLI; i++) {
            if (numerosLI[i] >= chave - 0.99 && numerosLI[i] <= chave + 0.99) {
                inserirCircular(&atual->sublista, numerosLI[i]);
                for (int j = i; j < countLI - 1; j++) {
                    numerosLI[j] = numerosLI[j + 1];
                }
                countLI--;
                i--;
            }
        }
        atual = atual->prox;
    }
}

void imprimirListaLE(ListaDuplamenteLigadaInt *lista, char *output) {
    NoDuploInt *atual = lista->inicio;
    strcat(output, "[");
    while (atual) {
        char buffer[50];
        sprintf(buffer, "%d(", atual->chave);
        strcat(output, buffer);

        NoCircular *sub = atual->sublista;
        if (sub) {
            NoCircular *inicio = sub;
            do {
                sprintf(buffer, "%g", sub->valor);
                strcat(output, buffer);
                sub = sub->prox;
                if (sub != inicio) strcat(output, "->");
            } while (sub != inicio);
        }
        strcat(output, ")");
        if (atual->prox) strcat(output, "->");
        atual = atual->prox;
    }
    strcat(output, "]");
}

void liberarListaLE(ListaDuplamenteLigadaInt *lista) {
    NoDuploInt *atual = lista->inicio;
    while (atual) {
        NoDuploInt *temp = atual;

        NoCircular *sub = atual->sublista;
        if (sub) {
            NoCircular *inicio = sub;
            NoCircular *prox;
            do {
                prox = sub->prox;
                free(sub);
                sub = prox;
            } while (sub != inicio);
        }

        atual = atual->prox;
        free(temp);
    }
    free(lista);
}

// Funções principais
void processarLinha(const char *linha, char *output) {
    float numerosLE[MAX_NUMBERS], numerosLI[MAX_NUMBERS];
    int countLE = 0, countLI = 0;

    char *token = strtok((char *)linha, " ");
    int isLI = 0;

    while (token) {
        if (strcmp(token, "LE") == 0) {
            isLI = 0;
        } else if (strcmp(token, "LI") == 0) {
            isLI = 1;
        } else {
            float valor = atof(token);
            if (isLI) {
                numerosLI[countLI++] = valor;
            } else {
                numerosLE[countLE++] = (int)valor;
            }
        }
        token = strtok(NULL, " ");
    }

    ListaDuplamenteLigadaInt *lista = inicializarListaInt();
    for (int i = 0; i < countLE; i++) {
        inserirOrdenadoInt(lista, (int)numerosLE[i]);
    }

    conectarLE_LI(lista, numerosLI, countLI);
    imprimirListaLE(lista, output);
    liberarListaLE(lista);
}

int main() {

    // Ponteiros para os arquivos de entrada e saída
    FILE *fp_in = fopen("L1Q3.in", "r"); // Abre o arquivo de leitura ("r")
    FILE *fp_out = fopen("L1Q3.out", "w"); // Abre o arquivo de escrita ("w")

    if (fp_in == NULL || fp_out == NULL) // Tratamento de erro
    {
        printf("File cannot be oppened");
        return EXIT_FAILURE;
    }

    char linha[BUFFER_SIZE];
    char result[BUFFER_SIZE] = "";
    while (fgets(linha, sizeof(linha), fp_in)) {
        char linhaResultado[BUFFER_SIZE] = "";
        processarLinha(linha, linhaResultado);
        strcat(result, linhaResultado);
        strcat(result, "\n");
    }

    fprintf(fp_out, "%s", result);

    fclose(fp_in);
    fclose(fp_out);

    return 0;
}