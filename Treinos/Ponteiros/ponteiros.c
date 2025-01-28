#include <stdlib.h>
#include <stdio.h>

// void descobrir_valores(int *vet, int *min, int *max, int tam){
//     int i;
//     *min = vet[0];
//     *max = vet[0];
//     for(i=0;i<tam;i++){
//         if(vet[i]<*min){
//             *min=vet[i];
//         }
//         if(vet[i]>*max){
//             *max=vet[i];
//         }
//     }

// }

// int main(void){
//     int vet[] = {50,10,250,1000,25}, *menor, *maior;
//     descobrir_valores(vet, &menor, &maior,5);
//     printf("Menor: %d\n",menor);
//     printf("Maior: %d\n",maior);
// }

typedef struct no{
    int valor;
    struct no *prox;    
}No;

No *insert_inicio(No *inicio, int num){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->valor = num;
        novo->prox = inicio;
    }
    return novo;
}

void insert_inicioV2(No **inicio, int num){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->valor = num;
        novo->prox = *inicio;
        *inicio = novo;
    }
}

void imprimir(No *inicio){
    if(inicio){
        printf("%d ",inicio->valor);
        imprimir(inicio->prox);
    }
}

int main(void){
    No *lista = NULL;
    // lista = insert_inicio(lista, 10);
    // lista = insert_inicio(lista, 100);
    // lista = insert_inicio(lista, 23);
    // lista = insert_inicio(lista, 2);
    insert_inicioV2(&lista, 10);
    insert_inicioV2(&lista, 100);
    insert_inicioV2(&lista, 23);
    insert_inicioV2(&lista, 2);
    imprimir(lista);
}