#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MaxCaractersLinha 1000

typedef struct no{
    int valor;
    int altura;
    struct no *esq;
    struct no *dir;
    struct no *pai;
}No;

typedef struct{
    No *raiz;
}Arvore;

No *criar_no(int num){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->valor=num;
        novo->altura=0; // (alt)
        novo->dir=NULL;
        novo->esq=NULL;
        novo->pai=NULL; // (pred)
    }
    else{
        printf("Erro ao alocar memória para novo nó\n");
    }
    return novo;
}

Arvore *criar_arv_vazia(){
    Arvore *nova = malloc(sizeof(Arvore));
    if(nova){
        nova->raiz=NULL;
    }
    else{
        printf("Erro ao alocar memória para árvore\n");
    }
    return nova;
}

void inserir_arv(Arvore *arvore, No *novo){
    if(arvore->raiz==NULL){
        arvore->raiz=novo;
    }
    else{
        No *walker = arvore->raiz;
        No *pai;
        int alt=0;
        while(walker!=NULL){
            pai=walker;
            if(novo->valor < walker->valor){
                walker = walker->esq;
            }
            else{
                walker = walker->dir;
            }
            alt++;
        }
        if(novo->valor < pai->valor){
            pai->esq = novo;
        }
        else{
            pai->dir = novo;
        }
        novo->pai = pai;
        novo->altura = alt;
    }
}

int main (void){
    // Ponteiros para os arquivos de entrada e saída
    FILE *fp_in = fopen("L2Q1.in", "r"); // Abre o arquivo de leitura ("r")
    // FILE *fp_out = fopen("L1Q1.out", "w"); // Abre o arquivo de escrita ("w")

    if (fp_in == NULL ) // Tratamento de erro || fp_out == NULL
    {
        printf("File cannot be oppened");
        return EXIT_FAILURE;
    }

    char line[MaxCaractersLinha];
    int valor;
    char *token;
    Arvore *arv;

    while(fgets(line, sizeof(line), fp_in) != NULL){
        // Usar strtok para dividir a linha em tokens (números)
        token = strtok(line, " \n"); // Delimitadores: espaço e nova linha

        // Criar árvore
        arv = criar_arv_vazia();

        while (token != NULL) {
            if (sscanf(token, "%d", &valor) == 1) {
                printf("%d\t", valor); // DEBUG

                // Inserção dos valores na árvore (a ser implementada)
                inserir_arv(arv,criar_no(valor));

            }
            token = strtok(NULL, " \n"); // Obter o próximo token
        }
        printf("\n"); // DEBUG
        
        // Impressão dos dados no arquivo imprimindo \n no começo da linha
        
        // Remoção do ultimo espaço

        // Excluir árvore

    }
    fclose(fp_in);
    // fclose(fp_out);
    return EXIT_SUCCESS;
}