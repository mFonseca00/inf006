#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct no{
    int chave;
    struct no *esq, *dir, *pai;  
}No;

typedef struct{
    No *raiz;
    int qtdNos;
}Arvore;

No *criar_no(int num){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->chave=num;
        novo->dir=NULL;
        novo->esq=NULL;
        novo->pai=NULL;
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
        nova->qtdNos=0;
    }
    else{
        printf("Erro ao alocar memória para árvore\n");
    }
    return nova;
}

Arvore *criar_arv(No *raiz){
    Arvore *nova = malloc(sizeof(Arvore));
    if(nova){
        nova->qtdNos=1;
        nova->raiz=raiz;
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
        while(walker!=NULL){
            pai=walker;
            if(novo->chave<walker->chave){
                walker = walker->esq;
            }
            else{
                walker = walker->dir;
            }
        }
        if(novo->chave < pai->chave){
            pai->esq = novo;
        }
        else{
            pai->dir = novo;
        }
        novo->pai = pai;
        arvore->qtdNos++;
    }
}

No *buscar_arv(Arvore *arvore, int busca){
    No *aux = arvore->raiz;
    while(aux!=NULL && aux->chave !=busca){
        if(aux->chave < busca){
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

No *remover_no(Arvore *arvore, int valor){
    No *walker = buscar_arv(arvore, valor); // Busca nó a ser removido
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
        walker->chave = sucessor->chave;
        
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
    arvore->qtdNos--;
    return walker;
}
