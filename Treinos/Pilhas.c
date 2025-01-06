#include <stdio.h>
#include <stdlib.h>

// Pilha - > Last in, First out (LIFO). As operações são realizadas no topo da pilha (ultimo elemento inserido).
// Possui apenas duas operaçõe: push(empilhar) e pop(desempilhar)

typedef struct no{
    int valor;
    struct no *proximo;
}No;

// função para operação PUSH
No* push(No *top, int valor){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->valor = valor;
        novo->proximo = top;
        return novo;
    }
    else{
        printf("Erro ao alocar memória");
    }
    return NULL;
}

No* pop(No **top){
    if(*top != NULL){
        No *remove = *top;
        *top = remove->prox; // ou: top->proximo
        return remove;
    }
    else{
        printf("Pilha vazia!\n");
    }
    return NULL;
}

void imprimir_pilha(No *top){
    printf("\n-----PILHA-----\n");
    while(top!=NULL){
        printf("%d",top->valor);
        top=top->prox;
    }
    printf("\n------FIM------\n");
}

int main(void){
    No *top = NULL, *removido = NULL;
    int opcao=-1;
    do{
        printf("\n0 - Sair\n1- PUSH\n2 - POP\n3 - Imprimir\n");
        switch (opcao){
            case 1:
                int valor;
                printf("\nDigite o valor a ser inserido: ");
                scanf("%d",&valor);
                top=push(top, valor);
                break;
            case 2:
                removido = pop(&top);
                if(removido!=NULL){
                    printf("Valor removido: %d\n", removido->valor);
                }
                else{
                    printf("Nenhum no removido\n");
                }
                break;
            case 3:
                imprimir_pilha();
                break;
            default:
                printf("\nOpcao invalida.\n");
                break;
        }
    }while(opcao!=0)
    
}
