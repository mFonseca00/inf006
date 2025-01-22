#include <stdlib.h>
#include <stdio.h>
#define max 10

typedef struct{
    int inicio, final, qtd;
    int dados[max];
}Fila;

Fila *criar_fila(){
    Fila *f = malloc(sizeof(Fila));
    if(f){
        f->inicio=0;
        f->final=0;
        f->qtd=0;
    }
    return f;
}

void liberar_fila(Fila *f){
    free(f);
}

int tamanho_fila(Fila *f){
    if(f){
        return f->qtd;
    }
    else{
        return -1;
    }
}

int fila_cheia(Fila *f){
    if(f){
        if(f->qtd==max){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return -1;
    }
}

int fila_vazia(Fila *f){
    if(f){
        if(f->qtd==0){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return -1;
    }
}

void inserir_fila(Fila *f, int num){
    if(f && fila_cheia(f) == 0 ){
        f->dados[f->final]=num;
        f->final = (f->final+1)%max;
        f->qtd++;
    }
    else{
        printf("Impossível inserir mais elementos. Fila cheia.");
    }
}

void remover_fila(Fila *f){
    int removido=-666;
    if(f && fila_vazia(f)==0){
        removido = f->dados[f->inicio];
        f->inicio = (f->inicio+1)%max;
        f->qtd++;
        printf("Elemento removido: %d\n",removido);
    }
    else{
        printf("Impossível remover elementos. Fila vazia.");
    }
}

void remover_fila(Fila *f){

}

int main(void){
    Fila *f;

}