// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>

// typedef struct node{
//     int data;
//     int h; // altura
//     struct node *left;
//     struct node *right;
// }Node;

// Node *novoNo(int num){
//     Node *novo = malloc(sizeof(Node));
//     if(novo){
//         novo->data = num;
//         novo->left=NULL;
//         novo->right=NULL;
//         novo->h=0;
//     }
//     else{
//         printf("\tErro ao alocar memória para novo no.\n");
//     }
//     return novo;
// }

// int maior(int a, int b){
//     return (a>b)? a: b;
// }

// int alturaNo(Node *no){
//     if(no == NULL){
//         return -1;
//     }
//     return no->h;
// }

// int fatorBalanceamento(Node *no){
//     if(no){
//         return (alturaNo(no->left)-alturaNo(no->right));
//     }
//     return 0;
// }

// /*
//        r
//         \
//          y
//        /  \          
//      f    outro no
// */

// Node *rotateLeft(Node *r){ // recebe a raiz da subárvore e retorna a nova raiz
//     Node *y, *f;
//     y = r->right; // Nó que irá virar a nova raiz
//     f = y->left; // Nó que armazena o filho a esquerda da nova raiz (se já houver)

//     y->left = r;
//     r->right = f;

//     r->h = maior(alturaNo(r->left),alturaNo(r->right) + 1);
//     y->h = maior(alturaNo(y->left),alturaNo(y->right) + 1);

//     return y;
// }

// /*
//             r
//           /
//         y
//       /  \          
// outro no   f
// */

// Node *rotateRight(Node *r){
//     Node *y, *f;
//     y = r->left;
//     f = y->right;

//     y->right = r;
//     r->left = f;

//     r->h = maior(alturaNo(r->left),alturaNo(r->right)) + 1;
//     y->h = maior(alturaNo(y->left),alturaNo(y->right)) + 1;

//     return y;
// }

// /*
//       r
//        \
//         no
//        /          
// outro no    
// */

// Node *rotateRightLeft(Node *r){ // Rotação dupla esquerda
//     r->right = rotateRight(r->right);
//     return rotateLeft(r);
// }

// /*
//       r
//     /
//   no
//     \          
//     outro no
// */

// Node *rotateLeftRight(Node *r){ // Rotação dupla direita
//     r->left = rotateLeft(r->left);
//     return rotateRight(r);
// }

// Node *balance(Node *root){
//     if (root == NULL) return NULL; // importante: não balancear NULL

//     int fb = fatorBalanceamento(root);

//     // Rotação à esquerda
//     if (fb < -1) {
//         if (fatorBalanceamento(root->right) <= 0) {
//             root = rotateLeft(root);
//         } else {
//             root = rotateRightLeft(root);
//         }
//     }
//     // Rotação à direita
//     else if (fb > 1) {
//         if (fatorBalanceamento(root->left) >= 0) {
//             root = rotateRight(root);
//         } else {
//             root = rotateLeftRight(root);
//         }
//     }


//     return root;
// }

// Node *insertNode(Node *root, int num){
//     if(root==NULL){ // Insere na raiz
//         return novoNo(num);
//     }
//     else{ // Insere após a raiz
//         if(num < root->data){
//             root->left = insertNode(root->left, num);
//         }
//         else if(num > root->data){
//             root->right = insertNode(root->right, num);
//         }
//         else{
//             printf("\tInserção não realizada. Valor %d ja existente.\n", num);
//         }
//     }

//     // Recalcula a altura
//     root->h = maior(alturaNo(root->left),alturaNo(root->right));

//     // Verifica se é necessário e rebalanceia a arvore
//     root = balance(root);

//     return root;
// }

// Node *removeAVL(Node *root, int num){
//     if(root == NULL){
//         printf("\tImpossivel remover. Arvore vazia.\n");
//         return NULL;
//     }
//     else{
//         if(num == root->data){ // Nó sem filhos
//             if(root->left == NULL && root->right == NULL){
//                 printf("\tElemento folha %d removido.\n", root->data);
//                 free(root);
//                 return NULL;
//             }
//             else{
//                 if(root->left != NULL && root->right != NULL){ // Nó com dois filhos
//                     // Encontra o predecessor
//                     Node *aux = root->left;
//                     while(aux->right){
//                         aux = aux->right;
//                     }
//                     // Troca o nó com o predecessor
//                     root->data = aux->data;
//                     aux->data = num;
//                     // Realiza a remoção (quando houver no máximo um filho)
//                     root->left = removeAVL(root->left, num);
//                     return root;
//                 }
//                 else{ // Remoção de Nó com um filho
//                     Node *aux;
//                     if(root->left != NULL){ // Filho a esquerda
//                         aux = root->left;
//                     }
//                     else{ // Filho a direita
//                         aux = root->right;
//                     }
//                     printf("\tElemento com 1 filho removido: %d\n", root->data);
//                     free(root);
//                     return aux;
//                 }
//             }
//         }
//         else{ // Caminha para encontrar valor
//             if(num < root->data){
//                 root->left = removeAVL(root->left, num);
//             }
//             else{
//                 root->right = removeAVL(root->right, num);
//             }
//         }

//         // Recalcula as alturas
//         root->h = maior(alturaNo(root->left),alturaNo(root->right)) + 1;

//         // Verifica se é necessário e rebalanceia
//         root = balance(root);

//         return root;

//     }
// }

// void printAVL(Node *root, int nivel){
//     int i;
//     if(root){
//         printAVL(root->right, nivel+1);
//         printf("\n\n");

//         for(i=0 ; i < nivel ; i++){
//             printf("\t");
//         }
//         printf("%d", root->data);
//         printAVL(root->left, nivel+1);
//     }
// }

// int main(void){
//     int op,valor;
//     Node *root = NULL;

//     do{
//         printf("\n\n\t0 - Sair\n\t1 - inserir\n\t2 - Remover\n\t3 - Imprimir\n\n");
//         scanf("%d", &op);
//         switch(op){
//             case 0:
//                 printf("\tSaindo...\n\n");
//                 break;
//             case 1:
//                 printf("\tDigite um valor para inserir: ");
//                 scanf("%d",& valor);
//                 root = insertNode(root, valor);
//                 break;
//             case 2:
//                 printf("\tDigite um valor para remover: ");
//                 scanf("%d",& valor);
//                 root = removeAVL(root, valor);
//                 break;
//             case 3:
//                 printAVL(root,1);
//                 break;
//             default:
//                 printf("\tOpcao invalida!\n");
//                 break;
//         }
//     }while(op!=0);

//     return 0;
// }

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
        printf("\tErro ao alocar memória para novo no.\n");
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

Node *rotateLeft(Node *r){
    Node *y, *f;
    y = r->right;
    f = y->left;

    y->left = r;
    r->right = f;

    // Recalcula a altura de r (IMPORTANTE: primeiro r)
    r->h = maior(alturaNo(r->left), alturaNo(r->right)) + 1;

    // Recalcula a altura de y
    y->h = maior(alturaNo(y->left), alturaNo(y->right)) + 1;

    return y;
}

Node *rotateRight(Node *r){
    Node *y, *f;
    y = r->left;
    f = y->right;

    y->right = r;
    r->left = f;

    // Recalcula a altura de r (IMPORTANTE: primeiro r)
    r->h = maior(alturaNo(r->left), alturaNo(r->right)) + 1;

    // Recalcula a altura de y
    y->h = maior(alturaNo(y->left), alturaNo(y->right)) + 1;

    return y;
}

Node *rotateRightLeft(Node *r){
    r->right = rotateRight(r->right);
    return rotateLeft(r);
}

Node *rotateLeftRight(Node *r){
    r->left = rotateLeft(r->left);
    return rotateRight(r);
}

Node *balance(Node *root){
    if (root == NULL) return NULL; // importante: não balancear NULL

    int fb = fatorBalanceamento(root);

    // Rotação à esquerda
    if (fb < -1) {
        if (fatorBalanceamento(root->right) <= 0) {
            root = rotateLeft(root);
        } else {
            root = rotateRightLeft(root);
        }
    }
    // Rotação à direita
    else if (fb > 1) {
        if (fatorBalanceamento(root->left) >= 0) {
            root = rotateRight(root);
        } else {
            root = rotateLeftRight(root);
        }
    }

    return root;
}

Node *insertNode(Node *root, int num){
    if(root==NULL){ // Insere na raiz
        return novoNo(num);
    }
    else{ // Insere após a raiz
        if(num < root->data){
            root->left = insertNode(root->left, num);
        }
        else if(num > root->data){
            root->right = insertNode(root->right, num);
        }
        else{
            printf("\tInserção não realizada. Valor %d ja existente.\n", num);
            return root; // Importante: retorna root inalterado
        }
    }

    // Recalcula a altura
    root->h = maior(alturaNo(root->left), alturaNo(root->right)) + 1;

    // Verifica se é necessário e rebalanceia a arvore
    root = balance(root);

    return root;
}

Node *removeAVL(Node *root, int num){
    if(root == NULL){
        printf("\tImpossivel remover. Arvore vazia.\n");
        return NULL;
    }
    else{
        if(num == root->data){ // Nó a ser removido encontrado

            if(root->left == NULL && root->right == NULL){ // Nó sem filhos
                printf("\tElemento folha %d removido.\n", root->data);
                free(root);
                return NULL;
            }
            else if(root->left != NULL && root->right != NULL){ // Nó com dois filhos
                // Encontra o predecessor (maior nó na subárvore esquerda)
                Node *aux = root->left;
                while(aux->right){
                    aux = aux->right;
                }

                // Troca os dados (NÃO o nó em si)
                root->data = aux->data;
                aux->data = num;

                // Remove o predecessor (agora folha ou com um filho)
                root->left = removeAVL(root->left, num);

            }
            else{ // Remoção de Nó com um filho
                Node *aux;
                if(root->left != NULL){ // Filho a esquerda
                    aux = root->left;
                }
                else{ // Filho a direita
                    aux = root->right;
                }
                printf("\tElemento com 1 filho removido: %d\n", root->data);
                free(root);
                return aux;
            }
        }
        else{ // Caminha para encontrar valor
            if(num < root->data){
                root->left = removeAVL(root->left, num);
            }
            else{
                root->right = removeAVL(root->right, num);
            }
        }

        if (root == NULL) return NULL; // Se a remoção deixou a árvore vazia.

        // Recalcula a altura (IMPORTANTE: +1)
        root->h = maior(alturaNo(root->left), alturaNo(root->right)) + 1;

        // Balanceia a árvore
        root = balance(root);

        return root;

    }
}

void printAVL(Node *root, int nivel){
    int i;
    if(root){
        printAVL(root->right, nivel+1);
        printf("\n\n");

        for(i=0 ; i < nivel ; i++){
            printf("\t");
        }
        printf("%d (%d)", root->data, root->h);
        printAVL(root->left, nivel+1);
    }
}

int main(void){
    int op,valor;
    Node *root = NULL;

    do{
        printf("\n\n\t0 - Sair\n\t1 - inserir\n\t2 - Remover\n\t3 - Imprimir\n\n");
        scanf("%d", &op);
        switch(op){
            case 0:
                printf("\tSaindo...\n\n");
                break;
            case 1:
                printf("\tDigite um valor para inserir: ");
                scanf("%d",& valor);
                root = insertNode(root, valor);
                break;
            case 2:
                printf("\tDigite um valor para remover: ");
                scanf("%d",& valor);
                root = removeAVL(root, valor);
                break;
            case 3:
                printAVL(root,1);
                break;
            default:
                printf("\tOpcao invalida!\n");
                break;
        }
    }while(op!=0);

    return 0;
}