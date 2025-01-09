#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct no{
    float valor;
    struct no *prox;
}No;

No *push(No *pilha, float num){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->valor = num;
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

float operacao(float n1, float n2, char op){
    switch(op){
        case '+':
            return n2+n1;
            break;
        case '-':
            return n2-n1;
            break;
        case '*':
            return n2*n1;
            break;
        case '/':
            return n2/n1;
            break;
        default:
            return 0.0;
    }
}

float resolverExpressao(char exp[]){
    char *slice;
    float num;
    No *n1,*n2,*pilha=NULL;

    slice = strtok(exp," ");
    while(slice){
        if(slice[0]=='+'||slice[0]=='-'||slice[0]=='*'||slice[0]=='/'){
            n1 = pop(&pilha);
            n2 = pop(&pilha);

            num = operacao(n1->valor,n2->valor,slice[0]);
            pilha = push(pilha, num);
            free(n1);
            free(n2);
        }
        else{
            num = strtol(slice, NULL, 10);
            pilha = push(pilha,num);
        }
        slice=strtok(NULL," ");
    }
    n1 = pop(&pilha);
    num = n1->valor;
    free(n1);
    return num;
}

int main(void){
    char exp[50] = {"5 2 /"};
    printf("\tExpressao: %s\t| Resultado: %.2f",exp,resolverExpressao(exp));
}