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
    Pilha auxP;
    initPilha(&auxP);
    No *removido = NULL;
    int qtdPop = 0;
    char strAux[MaxCaractersLinha];
    
    while (p->top != NULL && strcmp(p->top->nome, novoNome) > 0){
        // printf("Removendo da pilha principal...\n"); //DEBUG
        qtdPop++;
        removido = pop(p);
        if(removido){
            push(&auxP, removido->nome);
        }
    }

    push(p, novoNome);
    
    if(qtdPop>0){
        snprintf(retorno, MaxCaractersLinha,"%dx-pop",qtdPop,novoNome);
    }
    else{
        snprintf(retorno, MaxCaractersLinha,"push-%s",novoNome);
    }
    
    No *reInsert = auxP.top;
    while(reInsert){
        // printf("Devolvendo da pilha principal...\n"); //DEBUG
        push(p, reInsert->nome);
        snprintf(strAux,MaxCaractersLinha,"push-%s",reInsert->nome);
        strcat(retorno,strAux);
        reInsert = reInsert->prox;
    }
    // printf("%s\n", retorno); // DEBUG
}


int main(void) {
    FILE *fp_in = fopen("L1Q2.in", "r");
    FILE *fp_out = fopen("L1Q2.out", "w");

    if (fp_in == NULL || fp_out == NULL) {
        printf("File cannot be opened\n");
        return EXIT_FAILURE;
    }

    char line[MaxCaractersLinha];
    const char space[] = " ";
    char retorno[MaxCaractersLinha] = "";
    char saida[MaxCaractersLinha]= "";

    while (fgets(line, sizeof(line), fp_in) != NULL) {
        char *slice;
        Pilha p;
        initPilha(&p);
        slice = strtok(line, space);
        retorno[0] = '\0'; // Reinicia o buffer de retorno
        // printf("\n\nNova linha\n"); // DEBUG
        while (slice != NULL) {
            pushOrdenado(&p, slice, retorno);
            slice = strtok(NULL, space);
            // printf("%s\n", retorno); // DEBUG
            strcat(saida,retorno);
        }
        // imprimir_pilha(&p); // DEBUG
        printf("%s\n", saida); // DEBUG
        fprintf(fp_out, "%s\n", saida);
    }

    fclose(fp_in);
    fclose(fp_out);
    return EXIT_SUCCESS;
}