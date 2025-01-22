#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no *prox;
    struct no *anterior;
}No;

typedef struct{
    No *inicio;
    int tam;
}Lista;

void init_list(Lista *lista){
    lista ->inicio = NULL;
    lista->tam = 0;
}

void insert_inicio(Lista *lista, int num){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->valor=num;
        novo->anterior=NULL;
        if(lista->inicio==NULL){
            novo->prox=NULL;
            lista->inicio=novo;
        }
        else{
            novo->prox=lista->inicio;
            lista->inicio=novo;
        }
        lista->tam++;
    }
    else{
        printf("Erro ao alocar memória\n");
    }
}

void insert_fim(Lista *lista, int num){
    No *aux,*novo = malloc(sizeof(No));
    if(novo){
        novo->valor=num;
        novo->prox=NULL;
        aux=lista->inicio;
        if(aux==NULL){
            novo->anterior=NULL;
            lista->inicio=novo;
        }
        else{
            while(aux->prox){
            aux=aux->prox;
            }
            novo->anterior=aux;
            aux->prox=novo;
        }
        lista->tam++;
    }
    else{
        printf("Erro ao alocar memória\n");
    }
}

void insert_meio(Lista *lista, int num, int ref){//Inserir antes daquele valor
    No *aux,*novo = malloc(sizeof(No));
    if(novo){
        novo->valor=num;
        aux = lista->inicio;
        if(aux==NULL){
            novo->anterior=NULL;
            novo->prox=NULL;
            lista->inicio=novo;
            lista->tam++;
        }
        else{
            while(aux->prox->valor!=num && aux->prox!=NULL){
                aux=aux->prox;
            }
            if(aux->prox->valor==num){
                novo->prox=aux->prox;
                novo->anterior=aux;
                aux->prox->anterior=novo;
                aux->prox=novo;
                lista->tam++;
            }
            else{
                printf("Valor de referência não encontrado\n");
            }
        }
    }
    else{
        printf("Erro ao alocar memória\n");
    }
}

No *remove_inicio(Lista *lista){
    No *removed=NULL;
    if(lista->inicio){
        removed=lista->inicio;
        lista->inicio=NULL;
        lista->tam--;
    }
    else{
        printf("A Lista fornecida esta vazia. Impossível remover do início\n");
    }
    return removed;
}

No *remove_fim(Lista *lista){
    No *aux,*removed=NULL;
    if(lista->inicio){
        aux=lista->inicio;
        if(aux->prox==NULL){
            removed=aux;
            lista->inicio=NULL;
            lista->tam--;
        }
        else{
            while(aux->prox !=NULL){
                aux=aux->prox;
            }
            removed=aux;
            aux->anterior->prox=NULL;
            lista->tam--;
        }
    }
    else{
        printf("A Lista fornecida esta vazia. Impossível remover do final\n");
    }
    return removed;
}

No *remove_meio(Lista *lista, int ref){//Remover aquele valor
    No *aux,*removed=NULL;
    if(lista->inicio){
        aux=lista->inicio;
        while(aux!=NULL && aux->valor!=ref){
            aux=aux->prox;
        }
        if(aux->valor==ref){
            removed=aux;
            aux->anterior->prox = aux->prox;
            aux->prox->anterior = aux->anterior;
        }
        else{
            printf("Valor de referência não encontrado\n");
        }
    }
    else{
        printf("A Lista fornecida esta vazia. Impossível remover o valor fornecido\n");
    }
    return removed;
}

int main(void){
    
    return 0;
}