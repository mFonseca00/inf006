#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxCaractersLinha 1000
#define MaxNome 30

typedef struct no {
    char nome[MaxNome];
    struct no *prox;
} No;

typedef struct {
    int tam;
    No *top;
} Pilha;

void initPilha(Pilha *p) {
    p->top = NULL;
    p->tam = 0;
}

void push(Pilha *p, char nome[]) {
    No *novo = malloc(sizeof(No));
    if (novo) {
        strcpy(novo->nome, nome);
        novo->prox = p->top;
        p->top = novo;
        p->tam++;
    } else {
        printf("Erro ao alocar memória\n");
    }
}

No *pop(Pilha *p) {
    if (p->top != NULL) {
        No *remove = p->top;
        p->top = remove->prox;
        p->tam--;
        return remove;
    } else {
        printf("Pilha vazia!\n");
        return NULL;
    }
}

void imprimir_pilha(Pilha *p) {
    printf("\n-----PILHA de tamanho: %d-----\n\n", p->tam);
    No *aux = p->top;
    while (aux != NULL) {
        printf("%s\n", aux->nome);
        aux = aux->prox;
    }
    printf("\n------FIM------\n\n");
}

void pushOrdenado(Pilha *p, char novoNome[], char retorno[]){
   // Ponteiros para os arquivos de entrada e saída
    FILE *fp_in = fopen("L1Q1.in", "r"); // Abre o arquivo de leitura ("r")
    FILE *fp_out = fopen("L1Q1.out", "w"); // Abre o arquivo de escrita ("w")

    if (fp_in == NULL || fp_out == NULL) // Tratamento de erro
    {
        printf("File cannot be oppened");
        return EXIT_FAILURE;
    }

    char line[MaxCaractersLinha]; // Buffer para armazenar cada linha lida do arquivo
    const char space[] = " "; // Separador entre itens da linha
    

    
}

int main(void){
    
}