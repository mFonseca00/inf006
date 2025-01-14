#include <stdio.h>
#include <stdlib.h>

// Fila - > First in, First out (FIFO). As insersões são realizadas no final e as remoções, no início da fila.
// Possui apenas duas operaçõe: inserção e remoção


//MODO 1: pilha sem cabeçote (usa ponteiro para ponteiro)

// typedef struct no{
//     int valor;
//     struct no *prox;
// }No;

// void insert_fila(No **fila, int num){
//     No *aux,*novo = malloc(sizeof(No));
//     if(novo){
//         novo->valor = num;
//         nuvo->prox = NULL;
//         if(*fila == NULL){ //Caso seja o primeiro elemento da fila (fila vazia)
//             *fila = novo;
//         }
//         else{ //Caso não seja o primeiro elemento da fila
//             aux = *fila;
//             while(aux->prox){
//                 aux = aux->prox;
//             }
//             aux->prox = novo;
//         }
//     }
//     else{
//         printf("\n\n(!) - Erro ao alocar memória\n\n");
//     }
// }

// No *remove_fila(No **fila){
//     No *removed = NULL;

//     if(*fila){
//         removed = *fila;
//         *fila = removed->prox;        
//     }
//     else{
//         printf("\n\nFila vazia!\n\n")
//     }

//     return removed;
// }

// void print_fila(No *fila){
//     printf("\n-----FILA-----\n");
//     while(fila){
//         printf("%d ", fila->valor);
//         fila = fila->prox;
//     }
//     printf("\n-----FIM-----\n");
// }

// int main(void){
// No *removido, *fila =NULL;
// int opcao, num;

// do{
//     printf"0 - sair\n1 - inseri\n2 - remover\n3 - imprimir fila\n")
//     switch(opcao){
//         case 1:
//             printf("Digite o valor a inserir na fila:\t");
//             scanf("%d",&num);
//             insert_fila(&fila,num);
//             break;
//         case 2:
//             removido = *remove_fila(&fila);
//             printf("Valor removido da fila:\t%d\n", removido.valor);
//             free(removido);
//             break;
//         case 3:
//             print_fila(&fila);
//             break;
//         default:
//         if(opcao!=0){
//             printf("Opcao invalida!\n")
//         }      
//     }
//  }while(opcao!=0);
// }

//MODO 2: pilha com cabeçote

typedef struct no{
    int valor;
    struct no *prox;
}No;
