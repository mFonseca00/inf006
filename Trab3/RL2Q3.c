// Integrantes da dupla: Marcus Vinicius Silva da Fonseca (20241160005) e Roberto Silva Barreto (20241160031)

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
        if(busca < aux->valor ){
            aux = aux->esq;
        }
        else{
            aux = aux->dir;
        }
    }
    return aux;
}

No *maximo_arv(No *no){ // Busca o nó de maior valor naquela árvore ou sub-árvore
    No *aux = no;
    while(aux->dir != NULL){
        aux = aux->dir;
    }
    return aux;
}

No *minimo_arv(No *no){
    No *aux = no;
    while(aux->esq != NULL){
        aux = aux->esq;
    }
    return aux;
}

No *remover_folha(Arvore *arvore, No *no){
    if (no->pai != NULL) {
        if (no == no->pai->esq) {
            no->pai->esq = NULL;
        } else {
            no->pai->dir = NULL;
        }
    } else {
        // É a raiz
        arvore->raiz = NULL;
    }
    return no; // retorna o nó removido
}

No *remover_com_um_filho(Arvore *arvore, No* no) {
    No* filho = (no->esq != NULL) ? no->esq : no->dir;
    if (no->pai != NULL) {
        if (no == no->pai->esq) {
            no->pai->esq = filho;
        } else {
            no->pai->dir = filho;
        }
    } else {
        // É a raiz
        arvore->raiz = filho;
    }

    if (filho != NULL) {
        filho->pai = no->pai;
    }
    return no; // retorna o nó removido
}

No* encontrar_sucessor(No* no) {
    no = no->dir;
    while (no->esq != NULL) { // Busca o menor da direita
        no = no->esq;
    }
    return no;
}

No *remover_com_dois_filhos(Arvore* arvore, No* no) {
    // Usando o sucessor (menor da subárvore direita)
    No *sucessor = encontrar_sucessor(no);

    // Copiando as informações do sucessor
    no->valor = sucessor->valor; 
    no->altura = sucessor->altura;
    no->index = sucessor->index;
    no->soma = sucessor->soma;

    // Remoção
    return remover_com_um_filho(arvore, sucessor); // Remove o sucessor (que agora tem no máximo um filho)
}

No *remover_arv(Arvore *arvore, int valor) {
    No* no_a_remover = buscar_arv(arvore, valor);
    if (no_a_remover == NULL) {
        return no_a_remover; // Valor não encontrado
    }

    if (no_a_remover->esq == NULL && no_a_remover->dir == NULL) {
        return remover_folha(arvore, no_a_remover);
    } else if (no_a_remover->esq == NULL || no_a_remover->dir == NULL) {
        return remover_com_um_filho(arvore, no_a_remover);
    } else {
        return remover_com_dois_filhos(arvore, no_a_remover);
    }
}

void atualizar_altura_no(No *no, int altura){
    if(no){
        no->altura = altura;
        atualizar_altura_no(no->dir, altura+1);
        atualizar_altura_no(no->esq, altura+1);
    }
}

void atualizar_altura_arv(Arvore *arv, int alturaInicial){
    if(arv && arv->raiz){
        atualizar_altura_no(arv->raiz, 0);
    }
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
        line[strcspn(line, "\n")] = '\0'; // Remove o \n da linha lida
        line[strcspn(line, "\r")] = '\0'; // Remove o \r da linha lida
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
                    free(removido);
                    atualizar_altura_arv(arv, 0); // Atualiza a altura de cada nó após a remoção
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
