#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int data;
    int h; // altura
    struct node *left;
    struct node *right;
}Node;

Node *novoNo(int num){
    Node *novo = malloc(sizeof(Node));
    if(novo){
        novo->data = num;
        novo->left=NULL;
        novo->right=NULL;
        novo->h=0;
    }
    else{
        printf("Erro ao alocar memória para novo no.\n");
    }
    return novo;
}

int maior(int a, int b){
    return (a>b)? a: b;
}

int alturaNo(Node *no){
    if(no == NULL){
        return -1;
    }
    return no->h;
}

int fatorBalanceamento(Node *no){
    if(no){
        return (alturaNo(no->left)-alturaNo(no->right));
    }
    return 0;
}

/*
       r
        \
         y
       /  \          
     f    outro no
*/

Node *rotateLeft(Node *r){ // recebe a raiz da subárvore e retorna a nova raiz
    Node *y, *f;
    y = r->right; // Nó que irá virar a nova raiz
    f = y->left; // Nó que armazena o filho a esquerda da nova raiz (se já houver)

    y->left = r;
    r->right = f;

    r->h = maior(alturaNo(r->left),alturaNo(r->right) + 1);
    y->h = maior(alturaNo(y->left),alturaNo(y->right) + 1);

    return y;
}

/*
            r
          /
        y
      /  \          
outro no   f
*/

Node *rotateRight(Node *r){
    Node *y, *f;
    y = r->left;
    f = y->right;

    y->right = r;
    r->left = f;

    r->h = maior(alturaNo(r->left),alturaNo(r->right) + 1);
    y->h = maior(alturaNo(y->left),alturaNo(y->right) + 1);

    return y;
}

/*
      r
       \
        no
       /          
outro no    
*/

Node *rotateRightLeft(Node *r){ // Rotação dupla esquerda
    r->right = rotateRight(r->right);
    return rotateLeft(r);
}

/*
      r
    /
  no
    \          
    outro no
*/

Node *rotateLeftRight(Node *r){ // Rotação dupla direita
    r->left = rotateLeft(r->left);
    return rotateRight(r);
}

Node *balance(Node *root){
    int fb = fatorBalanceamento(root);

    // Rotação à esquerda
    if(fb < -1 && fatorBalanceamento(root->right) <=0 ){
        root = rotateLeft(root);
    }
    // Rotação à direita
    else if(fb > 1 && fatorBalanceamento(root->left) >=0 ){
        root = rotateRight(root);
    }
    // Rotação dupla à esquerda
    else if(fb > 1 && fatorBalanceamento(root->left) < 0 ){
        root = rotateLeftRight(root);
    }
    // Rotação dupla à direita
    else if(fb < -1 && fatorBalanceamento(root->right) > 0){
        root = rotateRightLeft(root);
    }

    return root;
}

Node *insertNode(Node *root, int num){
    if(root==NULL){ // Insere na raiz
        return novoNo(num);
    }
    else{ // Insere após a raiz
        if(num < root->data){
            root->left = insertNode(root->left);
        }
        else if(num > root->data){
            root->right = insertNode(root->left);
        }
        else{
            printf("\nInserção não realizada. Valor %d já existente.", num);
        }
    }

    // Recalcula a altura
    raiz->h = maior(alturaNo(root->left),alturaNo(root->right));

    // Verifica se é necessário e rebalanceia a arvore
    root = balance(root);

    return root;
}

