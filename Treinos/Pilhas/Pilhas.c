#include <stdio.h>
#include <stdlib.h>

// Pilha - > Last in, First out (LIFO). As operações são realizadas no topo da pilha (ultimo elemento inserido).
// Possui apenas duas operaçõe: push(empilhar) e pop(desempilhar)

//MODO 1: pilha sem cabeçote (usa ponteiro para ponteiro)

// typedef struct no{
//     int valor;
//     struct no *proximo;
// }No;

// No* push(No *top, int valor){
//     No *novo = malloc(sizeof(No));
//     if(novo){
//         novo->valor = valor;
//         novo->proximo = top;
//         return novo;
//     }
//     else{
//         printf("Erro ao alocar memória");
//     }
//     return NULL;
// }

// No* pop(No **top){
//     if(*top != NULL){
//         No *remove = *top;
//         *top = remove->prox; // ou: top->proximo
//         return remove;
//     }
//     else{
//         printf("Pilha vazia!\n");
//     }
//     return NULL;
// }

// void imprimir_pilha(No *top){
//     printf("\n-----PILHA-----\n");
//     while(top!=NULL){
//         printf("%d",top->valor);
//         top=top->prox;
//     }
//     printf("\n------FIM------\n");
// }

// int main(void){
//     No *top = NULL, *removido = NULL;
//     int opcao=-1;
//     do{
//         printf("\n0 - Sair\n1- PUSH\n2 - POP\n3 - Imprimir\n");
//         scanf("%d",&opcao);
//         switch (opcao){
//             case 1:
//                 int valor;
//                 printf("\nDigite o valor a ser inserido: ");
//                 scanf("%d",&valor);
//                 top=push(top, valor);
//                 break;
//             case 2:
//                 removido = pop(&top);
//                 if(removido!=NULL){
//                     printf("Valor removido: %d\n", removido->valor);
//                 }
//                 else{
//                     printf("Nenhum no removido\n");
//                 }
//                 break;
//             case 3:
//                 imprimir_pilha();
//                 break;
//             default:
//                 printf("\nOpcao invalida.\n");
//                 break;
//         }
//     }while(opcao!=0)
// }

//MODO 2: pilha com cabeçote

typedef struct no{
    int valor;
    struct no *prox;
}No;

typedef struct{
    No *top;
    int tam;
}Pilha;

void criar_pilha(Pilha *p){
    p->top = NULL;
    p->tam = 0;
}

void push(Pilha *p, int valor){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->valor = valor;
        novo->prox = p->top;
        p->top = novo;
        p->tam++;
    }
    else{
        printf("Erro ao alocar memória");
    }
}

No* pop(Pilha *p){
    if(p->top != NULL){
        No *remove = p->top;
        p->top = remove->prox;
        p->tam--;
        return remove;
    }
    else{
        printf("Pilha vazia!\n");
    }
    return NULL;
}

void imprimir_pilha(Pilha *p){
    printf("\n-----PILHA de tamanho: %d-----\n\n",p->tam);
    No *aux = p->top;
    while(aux!=NULL){
        printf("%d\n",aux->valor);
        aux=aux->prox;
    }
    printf("\n------FIM------\n");
    free(aux);
}

int main(void){
    No *removed = NULL;
    Pilha p;
    int opcao=-1;
    int insert;


    criar_pilha(&p);

    do{
        printf("\n\n------------------------------------MENU------------------------------------\n");
        printf("\n0 - Sair\n1 - PUSH\n2 - POP\n3 - Imprimir\n");
        scanf("%d",&opcao);
        switch (opcao){
            case 0:
                printf("\nSaindo...");
                break;
            case 1:
                printf("\nDigite o valor a ser inserido: ");
                scanf("%d",&insert);
                push(&p, insert);
                break;
            case 2:
                removed = pop(&p);
                if(removed!=NULL){
                    printf("Valor removido: %d\n", removed->valor);
                }
                else{
                    printf("Nenhum no removido\n");
                }
                free(removed);
                break;
            case 3:
                imprimir_pilha(&p);
                break;
            default:
                printf("\nOpcao invalida.\n");
                break;
        }
        printf("\n\n----------------------------------------------------------------------------\n");
    }while(opcao!=0);
    
}