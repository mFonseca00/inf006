#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MaxCaractersLinha 1000

typedef struct no{
    int valor;
    int altura;
    int index;
    int soma;
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
        novo->index=0; // numero de vezes que ocorreu
        novo->soma=0; // soma dos valores a direita - soma dos valores da esquerda (incrementa varrendo array com função após ler todas as linhas)
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
    if(arvore->raiz == NULL){
        arvore->raiz = novo;
    }
    else{
        No *walker = arvore->raiz;
        No *pai = NULL;  // Inicializa o ponteiro pai
        int alt = 0;
        while(walker != NULL){
            pai = walker; // Atualiza pai para o nó atual
            if(novo->valor < walker->valor){
                walker = walker->esq;
            }
            else{
                walker = walker->dir;
            }
            alt++;
        }
        // Atualiza o ponteiro do nó pai para o novo nó
        if(novo->valor == pai->valor){
            pai->index++;
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

No *maximo_arv(No *no){ // Busca o nó de maior valor naquela árvore ou sub-árvore
    No *aux = no;
    while(aux->dir != NULL){
        aux = aux->dir;
    }
    return aux;
}

int soma_subarvore(No *raiz) { // Realiza a soma dos valores de uma subarvore (esquerda ou direita)
    if (raiz == NULL) {
        return 0;
    }
    return raiz->valor + soma_subarvore(raiz->esq) + soma_subarvore(raiz->dir);
}

void calcular_soma_valores_arvore(No *raiz) { // Realiza a subtração dos valores da direita pela esquerda em cada nó da arvore
    if (raiz != NULL) {
        int somaEsq = soma_subarvore(raiz->esq);
        printf("No: %d\tsoma subarvore esquerda: %d\t",raiz->valor,somaEsq); // DEBUG
        int somaDir = soma_subarvore(raiz->dir);
        printf("No: %d\tsoma subarvore direita: %d\t",raiz->valor,somaDir); // DEBUG
        raiz->soma = somaDir - somaEsq; // Realiza a subtração entre a subarvore atual direita e atual esquerda
        printf("No: %d\tresultado entre subarvores: %d\n",raiz->valor,raiz->soma); // DEBUG

        calcular_soma_valores_arvore(raiz->esq); // Calcula para a esquerda
        calcular_soma_valores_arvore(raiz->dir); // Calcula para a direita
    }
}

void imprimir_dados_arquivo_arvore(No *raiz, FILE *fp_out){
    
    // O próprio nó
    fprintf(fp_out,"%d (%d)",raiz->valor,raiz->soma);
    // O nó a esquerda
    if(raiz->esq){
        fprintf(fp_out," ");
        imprimir_dados_arquivo_arvore(raiz->esq, fp_out);
    }
    // O nó a direita
    if(raiz->dir){
        fprintf(fp_out," ");
        imprimir_dados_arquivo_arvore(raiz->dir, fp_out);
    }
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
    FILE *fp_in = fopen("L2Q2.in", "r"); // Abre o arquivo de leitura ("r")
    FILE *fp_out = fopen("L1Q2.out", "w"); // Abre o arquivo de escrita ("w")

    if (fp_in == NULL || fp_out == NULL) // Tratamento de erro  
    {
        printf("File cannot be oppened");
        return EXIT_FAILURE;
    }

    char line[MaxCaractersLinha];
    int valor;
    char *token;
    Arvore *arv;
    int contLinha=0;

    while(fgets(line, sizeof(line), fp_in) != NULL){
        // Usar strtok para dividir a linha em tokens (números)
        token = strtok(line, " \n"); // Delimitadores: espaço e nova linha
        
        // Pula linha, caso não seja a primeira
        if(contLinha>0){
            fprintf(fp_out,"\n");
            printf("\n"); // DEBUG
        }
        contLinha++;

        // Criar árvore
        arv = criar_arv_vazia();

        while (token != NULL) {
            if (sscanf(token, "%d", &valor) == 1) {
                printf("%d ", valor); // DEBUG

                // Inserção dos valores na árvore
                inserir_arv(arv,criar_no(valor));

            }

            token = strtok(NULL, " \n"); // Obter o próximo token
        }

        printf("\n"); // DEBUG

        // Calculo da diferença entre as subarvores
        calcular_soma_valores_arvore(arv->raiz);

        // impressão em string no formato ou direto no arquivo
        imprimir_dados_arquivo_arvore(arv->raiz, fp_out);

        // Excluir árvore
        liberar_arvore(arv->raiz);
        free(arv);

    }
        
    fclose(fp_in);
    fclose(fp_out);
    return EXIT_SUCCESS;
}