#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MaxCaractersLinha 1000

typedef struct no{
    int valor;
    int altura;
    int index;
    int soma;
    struct no *esq;
    struct no *dir;
    struct no *pai;
}No;

No *criar_no(int num){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->valor=num;
        novo->altura=0; // (alt)
        novo->index=0; // numero de vezes que ocorreu
        novo->soma=0; // soma dos valores a direita - soma dos valores da esquerda (incrementa varrendo array com função após ler todas as linhas)
        novo->dir=NULL;
        novo->esq=NULL;
        novo->pai=NULL; // (pred)
    }
    else{
        printf("Erro ao alocar memória para novo nó\n");
    }
    return novo;
}

Arvore *criar_arv_vazia(){
    Arvore *nova = malloc(sizeof(Arvore));
    if(nova){
        nova->raiz=NULL;
    }
    else{
        printf("Erro ao alocar memória para árvore\n");
    }
    return nova;
}

int inserir_arv(Arvore *arvore, No *novo){
    if(arvore->raiz==NULL){
        arvore->raiz=novo;
    }
    else{
        No *walker = arvore->raiz;
        No *pai;
        int alt=0;
        while(walker!=NULL && pai->valor != novo->valor){
            pai=walker;
            if(novo->valor < walker->valor){
                walker = walker->esq;
            }
            else{
                walker = walker->dir;
            }
            alt++;
        }
        if(novo->valor == pai->valor){
            pai->index++;
        }
        if(novo->valor < pai->valor){
            pai->esq = novo;
        }
        else{
            pai->dir = novo;
        }
        novo->pai = pai;
        novo->altura = alt;
    }

    return novo->altura;
}

No *maximo_arv(No *no){ // Busca o nó de maior valor naquela árvore ou sub-árvore
    No *aux = no;
    while(aux->dir != NULL){
        aux = aux->dir;
    }
    return aux;
}

int soma_valores_arvore(No *raiz){ // Realiza recursivamente a soma dos valores a direita - somados valores a esquerda e armazena no no->soma
    int somaDir = 0, somaEsq = 0;
    if (raiz != NULL){
        

        somaDir = soma_valores_arvore(raiz->dir);
        somaEsq = soma_valores_arvore(raiz->esquerda);

        raiz->soma = somaDir-somaEsq;
    }
}

void liberar_arvore(No *raiz) {
    if (raiz != NULL) {
        liberar_arvore(raiz->esq); // Libera subárvore esquerda
        liberar_arvore(raiz->dir); // Libera subárvore direita
        free(raiz);                 // Libera o nó atual
    }
}