#include <stdlib.h>
#include <stdio.h>

typedef struct no{
  int valor;
  struct no *dir;
  struct no *esq;
}NoArv;

NoArv *insertArv_V1(NoArv *raiz, int num){
  NoArv *novo = malloc(sizeof(NoArv));
  if(novo){
    novo->valor = num;
    novo->esq = NULL;
    novo->dir = NULL;
    if(raiz == NULL){
      raiz=novo;
      return novo;
    }
    else{
      if(num<raiz->valor || num==raiz->valor){
        raiz->esq = insertArv_V1(raiz->esq, num);
      }
      else{
        raiz->dir = insertArv_V1(raiz->dir, num);
      }
      return raiz;
    }
  }
  else{
    printf("Erro ao alocar memoria\n");
  }
}

void printArv_preOrden(NoArv *raiz){
  if(raiz){
    printf("%d\t",raiz->valor);
    printArv_preOrden(raiz->esq);
    printArv_preOrden(raiz->dir);
  }
}

void printArv_orden(NoArv *raiz){
  if(raiz){
    printArv_preOrden(raiz->esq);
    printf("%d\t",raiz->valor);
    printArv_preOrden(raiz->dir);
  }
}

void printArv_posOrden(NoArv *raiz){
  if(raiz){
    printArv_preOrden(raiz->esq);
    printArv_preOrden(raiz->dir);
    printf("%d\t",raiz->valor);
  }
}

int main(void){

  NoArv *raiz = NULL;
  int opcao,num;

  do{
    printf("\n\n\t0 - sair\n\t1 - inserir\n\t2 - imprimir preOrden\n\t3 - imprimir orden\n\t4 - imprimir posOrden\n");
    scanf("%d",&opcao);
    printf("\n");
    switch(opcao){
      case 1:
        printf("\nInforme um numero para inserir:\t");
        scanf("%d",&num);
        raiz = insertArv_V1(raiz,num);
        break;
      case 2:
        printArv_preOrden(raiz);
        break;
      case 3:
        printArv_orden(raiz);
        break;
      case 4:
        printArv_posOrden(raiz);
        break;
      default:
        if(opcao!=0){
          printf("Opcao invalida\n");
        }
        break;
    }
  }while(opcao!=0);

  return 0;
}


// typedef struct no{
//   int valor;
//   struct no *dir;
//   struct no *esq;
// }NoArv;

// typedef struct {
//   NoArv *raiz;
//   int altura;
// }Arv;

// void initArv( Arv *arvore){
//   arvore->raiz=NULL;
//   arvore->altura=0;
// }