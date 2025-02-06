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

int inserir_arv(Arvore *arvore, No *novo){
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

    return novo->altura;
}

No *maximo_arv(No *no){ // Busca o nó de maior valor naquela árvore ou sub-árvore
    No *aux = no;
    while(aux->dir != NULL){
        aux = aux->dir;
    }
    return aux;
}

void liberar_arvore(No *raiz) {
    if (raiz != NULL) {
        liberar_arvore(raiz->esq); // Libera subárvore esquerda
        liberar_arvore(raiz->dir); // Libera subárvore direita
        free(raiz);                 // Libera o nó atual
    }
}

int main (void){
    // Ponteiros para os arquivos de entrada e saída
    FILE *fp_in = fopen("L2Q1.in", "r"); // Abre o arquivo de leitura ("r")
    FILE *fp_out = fopen("L1Q1.out", "w"); // Abre o arquivo de escrita ("w")

    if (fp_in == NULL || fp_out == NULL) // Tratamento de erro 
    {
        printf("File cannot be oppened");
        return EXIT_FAILURE;
    }

    char line[MaxCaractersLinha];
    int valor, altura;
    char *token;
    Arvore *arv;

    while(fgets(line, sizeof(line), fp_in) != NULL){
        // Usar strtok para dividir a linha em tokens (números)
        token = strtok(line, " \n"); // Delimitadores: espaço e nova linha

        // Criar árvore
        arv = criar_arv_vazia();

        while (token != NULL) {
            altura = -1;
            if (sscanf(token, "%d", &valor) == 1) {
                // printf("%d\t", valor); // DEBUG

                // Inserção dos valores na árvore
                altura = inserir_arv(arv,criar_no(valor));
                printf("%d ", altura); // DEBUG

                // Impressão da altura do nó inserido
                fprintf(fp_out,"%d ",altura);

            }
            token = strtok(NULL, " \n"); // Obter o próximo token
        }
        // Identificação do nó máximo
        No *max = maximo_arv(arv->raiz);
        
        // Impressão dos dados do valor máximo no arquivo
        fprintf(fp_out,"max %d alt %d ", max->valor, max->altura);
        printf("max %d alt %d\n", max->valor, max->altura); // DEBUG

        if(max->pai!=NULL){
            fprintf(fp_out,"pred %d", max->pai->valor);
            printf("pred %d\n", max->pai->valor); // DEBUG
        }
        else{
            fprintf(fp_out,"NAN");
            printf("NAN\n"); // DEBUG
        }

        // Adiciona a nova linha se não for a última linha
        if (fgets(line, sizeof(line), fp_in) != NULL) {
            fprintf(fp_out, "\n");
            fseek(fp_in, -strlen(line), SEEK_CUR); // Volta para a posição correta
        }

        // printf("\n"); // DEBUG
        // fprintf(fp_out,"\n",altura); // DEBUG

        // Excluir árvore
        liberar_arvore(arv->raiz);
        free(arv);
    }

    fclose(fp_in);
    fclose(fp_out);
    return EXIT_SUCCESS;
}