#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no *proximo;
}No;

typedef struct{
    int tam;
    No *topo;
}Pilha;

void criarPilha(Pilha *p){
    p->tam=0;
    p->topo=NULL;
}

void push(Pilha *pilha, int valor){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->proximo = pilha->topo;
        novo->valor = valor;
        pilha->topo = novo;
        pilha->tam++;
    }
    else{
        printf("\n(!)-Erro ao alocar memória.\n");
    }
}

No* pop(Pilha *pilha){
    if(pilha->topo == NULL){
        printf("\n(!)-Erro: Pilha Vazia!\n");
        return NULL;
    }
    No *removido = pilha->topo;
    pilha->topo = removido->proximo;
    pilha->tam--;
    return removido;
}

void imprimirPilha(Pilha *pilha){
    printf("\n\tPilha\n");
    No *aux = pilha->topo;
    while(aux){
        printf("\t%d\n", aux->valor);
        aux = aux->proximo;
    }
    printf("\n");
}

int fatorial(int num){
    Pilha p;
    criarPilha(&p);
    No *aux;
    while(num>1){
        push(&p,num);
        num--;
    }
    imprimirPilha(&p);// DEBUG
    while(p.topo){
        aux = pop(&p);
        num *= aux->valor;
        free(aux);
    }
    imprimirPilha(&p);// DEBUG
    return num;
}

int main(void){
    int num;
    printf("\nDigite um numero para calcular o fatorial:\t");
    scanf("%d",&num);
    printf("Fatorial: %d", fatorial(num));
    return 0;
}