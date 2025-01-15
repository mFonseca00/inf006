#include <stdio.h>
#include <stdlib.h>

//Pilha de prioridade (com inseção no meio)


typedef struct no{
    int valor;
    struct no *prox;
}No;

void insert_fila(No **fila, int num){
    No *aux,*novo = malloc(sizeof(No));
    if(novo){
        novo->valor = num;
        novo->prox = NULL;
        if(*fila == NULL){ //Caso seja o primeiro elemento da fila (fila vazia)
            *fila = novo;
        }
        else{ //Caso não seja o primeiro elemento da fila
            aux = *fila;
            while(aux->prox){
                aux = aux->prox;
            }
            aux->prox = novo;
        }
    }
    else{
        printf("\n\n(!) - Erro ao alocar memória\n\n");
    }
}

void priority_insert_fila(No **fila, int num){
    No *aux,*novo = malloc(sizeof(No));
    if(novo){
        novo->valor = num;
        novo->prox = NULL;
        if(*fila == NULL){ //Caso seja o primeiro elemento da fila (fila vazia)
            *fila = novo;
        }
        else{ //Caso não seja o primeiro elemento da fila
            if(num>59){ //Considerando todo número maior que 59 como prioridade
                if((*fila)->valor < 60){ //É a primeira prioridade?
                    novo->prox = *fila;
                    *fila = novo;
                }
                else{
                    aux = *fila;
                    while(aux->prox && aux->prox->valor > 59){ // Enquanto o próximo for prioridade
                        aux = aux->prox;
                    }
                    novo->prox = aux->prox;
                    aux->prox = novo;
                }
            }
            else{
                aux = *fila;
                while(aux->prox){
                    aux = aux->prox;
                }
                aux->prox = novo;
            }
            
        }
    }
    else{
        printf("\n\n(!) - Erro ao alocar memória\n\n");
    }
}

No *remove_fila(No **fila){
    No *removed = NULL;

    if(*fila){
        removed = *fila;
        *fila = removed->prox;        
    }
    else{
        printf("\n\nFila vazia!\n\n");
    }

    return removed;
}

void print_fila(No *fila){
    printf("\n-----FILA-----\n");
    while(fila){
        printf("%d ", fila->valor);
        fila = fila->prox;
    }
    printf("\n-----FIM-----\n");
}

int main(void){
No *removido, *fila =NULL;
int opcao, num;

do{
    printf("0 - sair\n1 - inserir\n2 - inserir como prioridade\n3 - remover\n4 - imprimir fila\n");
    scanf("%d",&opcao);
    switch(opcao){
        case 1:
            printf("Digite o valor a inserir na fila:\t");
            scanf("%d",&num);
            insert_fila(&fila,num);
            break;
        case 2:
            printf("Digite o valor a inserir na fila prioritária:\t");
            scanf("%d",&num);
            priority_insert_fila(&fila,num);
            break;
        case 3:
            removido = remove_fila(&fila);
            printf("Valor removido da fila:\t%d\n", removido->valor);
            free(removido);
            break;
        case 4:
            print_fila(fila);
            break;
        default:
        if(opcao!=0){
            printf("Opcao invalida!\n");
        }      
    }
 }while(opcao!=0);
}