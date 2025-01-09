#include <stdio.h>
#include <stdlib.h>

// ex:
//A pizza -> A azzip

typedef struct no{
    char caracter;
    struct no *prox;
}No;

No *push(No *pilha, char valor){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->caracter = valor;
        novo->prox = pilha;
        return novo;
    }
    printf("\t(!) - Erro ao alocar memória.\n");
    return NULL;
}

No *pop(No **pilha){
    No *removido = NULL;

    if(*pilha){
        removido = *pilha;
        *pilha = removido->prox;
    }
    else{
        printf("\tPilha vazia\n");
    }
    return removido;
}

void invertePalavras(char x[]){
    int i = 0;
    No *pilha = NULL, *removido;

    while(x[i]!='\0'){
        if(x[i] != ' '){
            pilha = push(pilha,x[i]);
        }
        else{
            while(pilha){
                removido = pop(&pilha);
                printf("%c", removido->caracter);
                free (removido);
            }
            printf(" ");
        }
        i++;
    }
    while(pilha){
        removido = pop(&pilha);
        printf("%c", removido->caracter);
        free (removido);
    }
}

int main(void){
    char exp[50] = {"ABRA A PORTA MARIQUINHA"};
    invertePalavras(exp);
}