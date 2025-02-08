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

No *buscar_arv(Arvore *arvore, int busca){
    No *aux = arvore->raiz;
    while(aux!=NULL && aux->valor != busca){
        if(aux->valor < busca){
            aux = aux->esq;
        }
        else{
            aux = aux->dir;
        }
    }
    return aux;
}

No *minimo_arv(No *no){ // Busca o nó de menor valor naquela árvore ou sub-árvore
    No *aux = no;
    while(aux->esq != NULL){
        aux = aux->esq;
    }
    return aux;
}

No *sucessor_arv(No *no){ // Busca o nó imediatamente superior
    if(no->dir!=NULL){
        return minimo_arv(no->dir);
    }
    //else
    No *aux = no;
    while(aux != NULL && aux->dir !=no){
        no = aux;
        aux = aux->pai;
    }
    return aux;
}

No *remover_arv(Arvore *arvore, int num){
    No *walker = buscar_arv(arvore, num); // Busca nó a ser removido
    if (!walker) return NULL; // Valor não encontrado na árvore
    
    No *pai = walker->pai;
    
    // Caso 1: Nó folha
    if (!walker->esq && !walker->dir) {
        if (!pai){
            arvore->raiz = NULL;
        }
        else if (pai->esq == walker){
            pai->esq = NULL;
        }
        else{
            pai->dir = NULL;
        } 
    }
    // Caso 2: Apenas um filho
    else if (!walker->dir || !walker->esq) {
        No *filho = walker->esq ? walker->esq : walker->dir;
        filho->pai = pai;
        if (!pai){
            arvore->raiz = filho;
            }
        else if (pai->esq == walker){
            pai->esq = filho;
        }
        else{
            pai->dir = filho;
        }
    }
    // Caso 3: Dois filhos
    else {
        No *sucessor = sucessor_arv(walker);
        walker->valor = sucessor->valor;
        
        // Ajustando ponteiros do sucessor
        if (sucessor->pai->esq == sucessor){
            sucessor->pai->esq = sucessor->dir;
        }
        else {
            sucessor->pai->dir = sucessor->dir;
        }
        
        if (sucessor->dir){
            sucessor->dir->pai = sucessor->pai;
            }
        
        walker = sucessor; // Agora walker aponta para o nó que será removido
    }
    return walker;
}

void imprimir_dados_arquivo_arvore(No *raiz, FILE *fp_out, bool primeiro){
    // O nó a esquerda
    if(raiz->esq){
        imprimir_dados_arquivo_arvore(raiz->esq, fp_out, primeiro);
        primeiro = false;
    }
    // O próprio nó
    if(!primeiro){
        fprintf(fp_out," ");
    }
    fprintf(fp_out,"%d (%d)",raiz->valor, raiz->altura);
    // O nó a direita
    if(raiz->dir){
        imprimir_dados_arquivo_arvore(raiz->dir, fp_out, false);
    }
}


void liberar_arvore(No *raiz) {
    if (raiz != NULL) {
        liberar_arvore(raiz->esq); // Libera subárvore esquerda
        liberar_arvore(raiz->dir); // Libera subárvore direita
        free(raiz);                // Libera o nó atual
    }
}

int main (void){
    // Ponteiros para os arquivos de entrada e saída
    FILE *fp_in = fopen("L2Q3.in", "r"); // Abre o arquivo de leitura ("r")
    FILE *fp_out = fopen("L2Q3.out", "w"); // Abre o arquivo de escrita ("w")

    if (fp_in == NULL || fp_out == NULL) // Tratamento de erro  
    {
        printf("File cannot be oppened");
        return EXIT_FAILURE;
    }

    char line[MaxCaractersLinha];
    int valor;
    char operacao;
    char *token;
    Arvore *arv;
    No *removido;
    bool primLinha=true;

    while(fgets(line, sizeof(line), fp_in) != NULL){
        // Usar strtok para dividir a linha em tokens (números)
        token = strtok(line, " \n"); // Delimitadores: espaço e nova linha
        printf("\nNova linha"); // DEBUG
        
        // Pula linha, caso não seja a primeira
        if(!primLinha){
            fprintf(fp_out,"\n");
            printf("\n"); // DEBUG
        }
        primLinha = false;

        // Criar árvore
        arv = criar_arv_vazia();

        while (token != NULL) {
            printf("\nProxima leitura:\t"); // DEBUG
            if (sscanf(token, "%c", &operacao)==1) {
                printf("Operacao: %c\t", operacao); // DEBUG
                
            }
            token = strtok(NULL, " \n"); // Obter o próximo token
            if (sscanf(token, "%d", &valor)==1) {
                printf("Valor: %d", valor); // DEBUG
            }
            token = strtok(NULL, " \n"); // Obter o próximo token
            if(operacao =='a'){
                // Inserção dos valores na árvore
                inserir_arv(arv,criar_no(valor));
                printf("\tNo inserido."); // DEBUG
            }
            if(operacao == 'r'){
                // se for r e existir esse nó, remove, caso contrário, insere (função remover deve ter retorno)
                removido = remover_arv(arv,valor);
                if(removido!=NULL){
                    printf("\tNo de valor %d removido.", removido->valor); // DEBUG
                }
                else{
                    printf("\tImpossivel remover no inexistente."); // DEBUG
                    inserir_arv(arv,criar_no(valor));
                    printf("\tNo inserido."); // DEBUG
                }
            }
        }

        printf("\n"); // DEBUG

        // impressão dos valores e os resultados no arquivo
        imprimir_dados_arquivo_arvore(arv->raiz, fp_out, true);

        // Excluir árvore
        liberar_arvore(arv->raiz);
        free(arv);

    }
    fclose(fp_in);
    fclose(fp_out);
    return EXIT_SUCCESS;
}