#include <stdlib.h>
#include <stdio.h>

typedef struct no{
  int valor;
  struct no *dir;
  struct no *esq;
}NoArv;

typedef struct {
  No *raiz;
  int altura;
}Arv;

initArv( Arv *arvore){
  arvore->raiz=NULL;
  arvore->altura=0;
}

insertArv(Arv *arvore, int num){
  NoArv *novo = malloc(sizeof(No));
  if(novo){
    novo->valor = num;
    novo->esq = NULL;
    novo->dir = NULL;
    if(arvore->raiz == NULL){
      arvore->raiz=novo;
      arvore->altura++;
    }
    else{
      
    }
  }
  else{
    printf("Erro ao alocar memoria\n");
}

int main(void){
  return 0;
}
