#include <stdlib.h>
#include <stdio.h>

typedef struct no{
  int valor;
  struct no *dir;
  struct no *esq;
}NoArv;

NoArv *insertArv_V1(NoArv *raiz, int num){ //Recursiva com retorno
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

void insertArv_V2(NoArv **raiz, int num){ //Recursiva sem retorno (ponteiro para ponteiro)
  if(*raiz==NULL){
    *raiz = malloc(sizeof(NoArv));
    (*raiz)->valor=num;
    (*raiz)->esq=NULL;
    (*raiz)->dir=NULL;
  }
  else{
    if(num<=(*raiz)->valor){
      insertArv_V2(&((*raiz)->esq),num);
    }
    else{
      insertArv_V2(&((*raiz)->dir),num);
    }
  }
}

void insertArv_V3(NoArv **raiz, int num){ //Não recursiva e sem retorno
  NoArv *aux = *raiz;
  while(aux){
    if(num<=aux->valor){
      raiz = &aux->esq;
    }
    else{
      raiz = &aux->dir;
    }
    aux = *raiz;
  }
  aux = malloc(sizeof(NoArv));
  aux->valor=num;
  aux->dir=NULL;
  aux->esq=NULL;
  *raiz = aux;
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
    printf("\n\n\t0 - sair\n\t1 - inserir\n\t2 - imprimir\n");
    scanf("%d",&opcao);
    printf("\n");
    switch(opcao){
      case 1:
        printf("\nInforme um numero para inserir:\t");
        scanf("%d",&num);
        // raiz = insertArv_V1(raiz,num);
        // insertArv_V2(&raiz,num);
        insertArv_V3(&raiz,num);
        break;
      case 2:
        printf("Impressão preOrden:\n");
        printArv_preOrden(raiz);
        printf("\nImpressão orden:\n");
        printArv_orden(raiz);
        printf("\nImpressão posOrden:\n");
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