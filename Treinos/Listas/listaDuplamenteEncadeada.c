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