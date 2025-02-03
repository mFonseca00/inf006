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

void insertArv_V3(NoArv **raiz, int num){ //Não recursiva e sem retorno (iterativa)
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

NoArv *buscaArv_recursiva(NoArv *raiz, int num){
  if(raiz){
    if(num == raiz->valor){
      return raiz;
    }
    else if(num<raiz->valor){
      return buscaArv_recursiva(raiz->esq,num);
    }
    else{
      return buscaArv_recursiva(raiz->dir,num);
    }
  } 
  return NULL; 
}

NoArv *buscarArv_iterativa(NoArv *raiz, int num){
  while(raiz){
    if(num==raiz->valor){
      return raiz;
    }
    else if(num<raiz->valor){
      raiz = raiz->esq;
    }
    else{
      raiz = raiz->dir;
    }
  }
  return NULL;
}

NoArv *removeNoArv(NoArv *raiz, int chave){
  if(raiz==NULL){
    printf("Valor nao encontrado!\n");
    return NULL;
  }
  else{
    if(raiz->valor == chave){
      if(raiz->esq == NULL && raiz->dir==NULL){// Remoção de nós sem filhos
        free(raiz);
        return NULL;
      }
      else{// Remoção de nós com filhos

      }
    }
    else{
      if(raiz->valor > chave){
        raiz->esq = removeNoArv(raiz->esq,chave);
      }
      else{
        raiz->dir = removeNoArv(raiz->dir,chave);
      }
      return raiz;
    }
  }
}

int alturaArv_recursiva(NoArv *raiz){
  if(raiz == NULL){
    return -1;
  }
  else{
    int esq = alturaArv_recursiva(raiz->esq);
    int dir = alturaArv_recursiva(raiz->dir);
    if(esq>dir){
      return esq+1;
    }
    else{
      return dir+1;
    }
  }
}

int qtdNosArv_recursiva(NoArv *raiz){
  if(raiz==NULL){
    return 0;
  }
  else{
    return 1 + qtdNosArv_recursiva(raiz->dir) + qtdNosArv_recursiva(raiz->esq);
  }
}

int qtdFolhasArv_recursiva(NoArv *raiz){ //Apenas extremidades da árvore
  if(raiz==NULL){
    return 0;
  }
  else if(raiz->esq==NULL && raiz->dir==NULL){
    return 1;
  }
  else{
    return qtdFolhasArv_recursiva(raiz->esq) + qtdFolhasArv_recursiva(raiz->dir);
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

  NoArv *busca, *raiz = NULL;
  int opcao,num;

  do{
    printf("\n\n\t0 - sair\n\t1 - inserir\n\t2 - imprimir\n\t3 - Buscar valor\n\t4 - Altura\n\t5 - Qtd Nos\n\t6 - Folhas\n\t7 - Remover No\n\n");
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
        printf("\n\tImpressão preOrden:\n");
        printArv_preOrden(raiz);
        printf("\n\tImpressão orden:\n");
        printArv_orden(raiz);
        printf("\n\tImpressão posOrden:\n");
        printArv_posOrden(raiz);
        break;
      case 3:
        printf("\nInforme um numero para buscar:\t");
        scanf("%d",&num);
        // busca = buscaArv_recursiva(raiz,num);
        busca = buscarArv_iterativa(raiz,num);
        if(busca){
          printf("\n\tValor %d Encontrado",busca->valor);
        }
        else{
          printf("\n\tValor não encontrado");
        }        
        break;
      case 4:
        printf("\n\tAltura da arvore: %d",alturaArv_recursiva(raiz));
        break;
      case 5:
        printf("\n\tQuantidade de Nos na Arvore: %d",qtdNosArv_recursiva(raiz));
        break;
      case 6:
        printf("\n\tQuantidade de Folhas na Arvore: %d",qtdFolhasArv_recursiva(raiz));
        break;
      case 7:
        printf("\nInforme um numero para remover:\t");
        scanf("%d",&num);
        raiz removeNoArv(raiz,num);
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