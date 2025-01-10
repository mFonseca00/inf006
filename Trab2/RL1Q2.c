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
    Pilha pilhaAux;
    initPilha(&pilhaAux);

    No *nomeTopo = p->top, *removido;
    int qtdPop=0;
    
    // Percorre pilha original, verificando se cada nome deve ser posicionado antes ou depois do novo
    while(p->top != NULL && strcmp(nomeTopo->nome,novoNome)>0){
        removido = pop(p); // remove o nome que deve ser posicionaado depois
        if(removido){
            qtdPop++; // contabiliza a remoção
            push(&pilhaAux,removido->nome); // insere o nome removido na pilha auxiliar
        }
    }

    // retornar texto informando quantos pop houveram (apenas se houve)
    push(p,novoNome); // insere o novo nome em sua posição na pilha original
    // retornar texto de inserção do nome

    // Re-inserção de elementos na pilha original:
    // Percorre pilha auxiliar, movendo seus elementos para a pilha original
    No *reInsert = pilhaAux.top;
    while(reInsert){
        push(p,reInsert->nome);
        // retornar texto de inserção do nome
        reInsert = reInsert->prox;
    }
}

int main(void){
    // Ponteiros para os arquivos de entrada e saída
    FILE *fp_in = fopen("L1Q2.in", "r"); // Abre o arquivo de leitura ("r")
    FILE *fp_out = fopen("L1Q2.out", "w"); // Abre o arquivo de escrita ("w")
    if (fp_in == NULL || fp_out == NULL) // Tratamento de erro
    {
    printf("File cannot be oppened");
    return EXIT_FAILURE;
    }

    char line[MaxCaractersLinha]; // Buffer para armazenar cada linha lida do arquivo
    const char space[] = " "; //Separador entre os nomes no arquivo de entrada

    while (fgets(line, sizeof(line), fp_in) != NULL)
    {
        char *slice;
        char retorno[MaxCaractersLinha];
        slice = strtok(line, space);
        printf("\n\nNova linha\n"); // DEBUG

        Pilha p;// Cria a pilha
        initPilha(&p);// Inicia a pilha para armazenar os nomes

        while(slice!=NULL){

            pushOrdenado(&p,slice,retorno);

            slice = strtok(NULL,space);
        }
        
        imprimir_pilha(&p);
        fputs(retorno,fp_out);

    }
}