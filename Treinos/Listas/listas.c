#include <stdio.h>
#include <stdlib.h>

// Lista - > Não possui regra para inserção ou remoção de nó. Estrutura mais genérica
// Pode possuir diferentes operações

//MODO 1: lista simplesmente encadeada sem cabeçote (usa ponteiro para ponteiro)

// typedef struct no{
//     int valor;
//     struct no *prox;
// }No;

// void insert_inicio(No **lista, int num){
//     No *novo=malloc(sizeof(No));
//     if(novo){
//         novo->valor = num;
//         novo->prox = *lista;
//         *lista = novo;
//     }
//     else{
//         printf("Falha ao alocar memória para o novo no");
//     }
// }

// void insert_fim(No **lista, int num){
//     No *novo=malloc(sizeof(No)),*aux;
//     if(novo){
//         novo->valor=num;
//         novo->prox=NULL;
        
//         if(*lista==NULL){
//             *lista = novo;
//         }
//         else{
//             aux=*lista;
//             while(aux->prox){
//                 aux = aux->prox;
//             }
//             aux->prox=novo;
//         }
        
//     }
//     else{
//         printf("Falha ao alocar memória para o novo no\n");
//     }
// }

// void insert_meio(No **lista, int num, int anterior){
//     No *novo=malloc(sizeof(No)),*aux;
//     int i=0;
//     if(novo){
//         novo->valor=num;
//         if(*lista==NULL){
//             novo->prox = NULL;
//             *lista = novo;
//             printf("Lista vazia, adicionando como primeiro elemento\n");
//         }
//         else{
//             aux=*lista;
//             while(i<anterior && aux->prox){
//                 aux = aux->prox;
//                 i++;
//             }
//             if(i<anterior){
//                 printf("Valor de referência não encontrado, adicionando ao final da lista\n");
//             }
//             novo->prox=aux->prox;
//             aux->prox=novo;
//         }
//     }
//     else{
//         printf("Falha ao alocar memória para o novo no\n");
//     }
// }

// void print_lista(No *lista){
//     printf("\n-----Lista-----\n");
//     while(lista){
//         printf("%d\t",lista->valor);
//         lista=lista->prox;
//     }
//     printf("\n---------------\n");

// }

// int main(void){
//     No *removido, *lista =NULL;
//     int opcao, num, ant;

//     do{
//         printf("0 - sair\n1 - inserir no inicio\n2 - inserir no meio\n3 - inserir no fim\n4 - imprimir lista\n");
//         scanf("%d",&opcao);
//         switch(opcao){
//             case 1:
//                 printf("Digite o valor a inserir na lista:\t");
//                 scanf("%d",&num);
//                 insert_inicio(&lista,num);
//                 break;
//             case 2:
//                 printf("Digite o valor a inserir na lista e a posicao de referencia(anterior):\t");
//                 scanf("%d%d",&num, &ant);
//                 insert_meio(&lista,num,ant);
//                 break;
//             case 3:
//                 printf("Digite o valor a inserir na lista:\t");
//                 scanf("%d",&num);
//                 insert_fim(&lista,num);
//                 break;
//             case 4:
//                 print_lista(lista);
//                 break;
//             default:
//                 if(opcao!=0){
//                     printf("Opcao invalida!\n");
//                 }
//                 break;     
//         }
//     }while(opcao!=0);
// }

//MODO 2: lista simplesmente encadeada com cabeçote

typedef struct no{
    int valor;
    struct no *prox;
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
    No *novo=malloc(sizeof(No));
    if(novo){
        novo->valor = num;
        novo->prox = lista->inicio;
        lista->inicio = novo;
        lista->tam++;
    }
    else{
        printf("Falha ao alocar memória para o novo no");
    }
}

void insert_fim(Lista *lista, int num){
    No *novo=malloc(sizeof(No)),*aux;
    if(novo){
        novo->valor = num;
        novo->prox=NULL;
        
        if(lista->inicio==NULL){
            lista->inicio = novo;
        }
        else{
            aux=lista->inicio;
            while(aux->prox){
                aux = aux->prox;
            }
            aux->prox=novo;
        }
        lista->tam++;
    }
    else{
        printf("Falha ao alocar memória para o novo no\n");
    }
}

void insert_meio(Lista *lista, int num, int anterior){
    No *novo=malloc(sizeof(No)),*aux;
    if(novo){
        novo->valor=num;
        if(lista->inicio==NULL){
            novo->prox = NULL;
            lista->inicio = novo;
        }
        else{
            aux=lista->inicio;
            while(aux->valor != anterior && aux->prox){
                aux = aux->prox;
            }
            novo->prox=aux->prox;
            aux->prox=novo;
        }
        lista->tam++;
    }
    else{
        printf("Falha ao alocar memória para o novo no\n");
    }
}

void insert_ord(Lista *lista, int num){
    No *novo=malloc(sizeof(No)),*aux;
    if(novo){
        novo->valor=num;
        if(lista->inicio==NULL){
            novo->prox = NULL;
            lista->inicio = novo;
        }
        else if(novo->valor < lista->inicio->valor){
            novo->prox = lista->inicio->prox;
            lista->inicio = novo;
        }
        else{
            aux=lista->inicio;
            while(aux->prox && aux->prox->valor < novo->valor){
                aux=aux->prox;
            }
            novo->prox=aux->prox;
            aux->prox=novo;
        }
        lista->tam++;
    }
    else{
        printf("Falha ao alocar memória para o novo no\n");
    }
}

No *remove_from_list(Lista *lista, int num){
    No *removed = NULL, *aux;
    if(lista->inicio){
        if(lista->inicio->valor == num){
            removed = lista->inicio;
            lista->inicio = lista->inicio->prox;
            lista->tam--;
        }
        else{
            aux = lista->inicio;
            while(aux->prox && aux->prox->valor != num){
                aux = aux->prox;
            }
            if(aux->prox){
                removed = aux->prox;
                aux->prox = removed->prox;
                lista->tam--;
            }
            else{
                printf("\nElemento com valor %d nao foi encontrado\n", num);
            }
        }
    }
    else{
        printf("\nLista vazia\n");
    }
    return removed;
}

No *search_from_list(Lista *lista, int num){
    No *aux,*buscado=NULL;
    aux = lista->inicio;
    while(aux && aux->valor != num){
        aux = aux->prox;
    }
    if(aux){
        buscado = aux;
    }
    
    return buscado;
}

void print_lista(Lista *lista){
    No *aux = lista->inicio;
    printf("\n-----Lista Tam:%d-----\n",lista->tam);
    while(aux){
        printf("%d\t",aux->valor);
        aux=aux->prox;
    }
    printf("\n----------------------\n\n");

}

void cat_list(Lista *list, Lista *insertlist){
    No *aux = insertlist->inicio;
    while(aux){
        insert_ord(list, aux->valor);
        aux=aux->prox;
    }
}

int main(void){
    No *removido,*busca;
    Lista lista, listaA, listaB;
    init_list(&listaA);
    init_list(&listaB);
    init_list(&lista);
    int opcao, num, ant;

    do{
        printf("\n0 - sair\n1 - inserir no inicio\n2 - inserir no meio\n3 - inserir no fim\n4 - inserir ordenado\n5 - remover valor\n6 - Imprimir Lista\n7 - Buscar valor\n8 - copiar\n");
        scanf("%d",&opcao);
        switch(opcao){
            case 1:
                printf("Digite o valor a inserir na lista A:\t");
                scanf("%d",&num);
                insert_inicio(&listaA,num);
                printf("Digite o valor a inserir na lista B:\t");
                scanf("%d",&num);
                insert_inicio(&listaB,num);
                break;
            case 2:
                printf("Digite o valor a inserir na lista A e o valor de referencia(anterior):\t");
                scanf("%d%d",&num, &ant);
                insert_meio(&listaA,num,ant);
                printf("Digite o valor a inserir na lista B e o valor de referencia(anterior):\t");
                scanf("%d%d",&num, &ant);
                insert_meio(&listaB,num,ant);
                break;
            case 3:
                printf("Digite o valor a inserir na lista A:\t");
                scanf("%d",&num);
                insert_fim(&listaA,num);
                printf("Digite o valor a inserir na lista B:\t");
                scanf("%d",&num);
                insert_fim(&listaB,num);
                break;
            case 4:
                printf("Digite o valor a inserir na listaA:\t");
                scanf("%d",&num);
                insert_ord(&listaA,num);
                printf("Digite o valor a inserir na listaB:\t");
                scanf("%d",&num);
                insert_ord(&listaB,num);
                break;
            case 5:
                printf("Digite o valor a remover da lista:\t");
                scanf("%d",&num);
                removido = remove_from_list(&lista,num);
                if(removido){
                    printf("\nElemento de valor %d removido\n",removido->valor);
                    free(removido);
                }
                else{
                    printf("\nNao foi possivel remover um elemento com valor %d\n",num);
                }
                break;
            case 6:
                printf("Lista A: ");
                print_lista(&listaA);
                printf("Lista B: ");
                print_lista(&listaB);
                printf("Lista Final: ");
                print_lista(&lista);
                break;
            case 7:
                printf("Digite o valor a buscar na lista:\t");
                scanf("%d",&num);
                busca = search_from_list(&lista,num);
                if(busca){
                    printf("Valor %d encontrado\n",busca->valor);
                    free(busca);
                }
                else{
                    printf("Valor nao encontrado\n");
                }
                break;
            case 8:
                cat_list(&lista,&listaA);
                cat_list(&lista,&listaB);
                break;
            default:
                if(opcao!=0){
                    printf("Opcao invalida!\n");
                }
                break;     
        }
    }while(opcao!=0);
}