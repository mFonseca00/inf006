#include <stdio.h>
#include <stdlib.h>

// ex:
//3*[(5-2)/5] - certo
//3*[(5-2)/5 - errado

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

void imprimirPilha(No *pilha){
    printf("\tPILHA\n");
    while(pilha){
        printf("\t%c\n", pilha->caracter);
        pilha = pilha->prox;
    }
    printf("\tFIM PILHA\n\n");
}

int formaPar(char f, char d){
    switch(f){
        case ')':
            if(d == '(')
                return 1; //certo
            else
                return 0; //errado
            break;
        case ']':
            if(d == ']')
                return 1;
            else
                return 0;
            break;
        case '}':
            if(d == '}')
                return 1;
            else
                return 0;
            break;
    }
}

int identificaFormacao(char x[]){
    int i = 0;
    No *pilha = NULL, *removido;

    while(x[i]!='\0'){
        if(x[i] == '{' || x[i] == '[' || x[i] == '('){
            pilha = push(pilha,x[i]);
            imprimirPilha(pilha);
        }
        else if(x[i] == '}' || x[i] == ']' || x[i] == ')'){
            removido = pop(&pilha);
            if(removido){
                if(formaPar(x[i],removido->caracter) == 0){
                    printf("\tExpressao mal formada\n");
                    return 1;
                }
                free (removido);
            }
            else{
                printf("\tExpressao mal formada\n");
                return 1;
            }
        }
        i++;
    }
    imprimirPilha(pilha);
    if(pilha){
        printf("\texpressao mal formada\n");
        return 1;
    }
    else{
        printf("\texpressao vazia\n");
        return 0;
    }

}

int main(void){
    char exp[50];
    printf("\tDigite uma expressao:\t");
    scanf("%49[^\n]",&exp);
    printf("\n\tExpressao:\t %s\n\tRetorno:\t %d\n", exp, identificaFormacao(exp));
}