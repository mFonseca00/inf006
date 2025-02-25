#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int data;
    struct node *left;
    struct node *right;
}Node;

Node *insert(Node *root, int data){
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    if(root == NULL){
        root=temp;
    }
    else {
        Node *current = root;
        Node *parent = NULL;
        while(1){
            parent = current;
            if(data<parent->data){
                current = current->left;
                if(current == NULL){
                    parent->left = temp;
                    return root;
                }
            }
            else{
                current = current->right;
                if(current == NULL){
                    parent->right = temp;
                    return root;
                }
            }
        }
    }
    return root;
}

Node *search(Node *root, int num){
    Node *current = root;
    printf("\nVisitng elements: ");
    while(current){
        printf("%d ... ", current->data);

        if(num < current->data){
            current = current->left;
        }
        else if(num > current->data){
            current = current->right;
        }
        else{
            return current;
        }
    }
}

void inorder_traversal(Node *root){
    if(root){
        inorder_traversal(root->left);
        printf("%d ",root->data);
        inorder_traversal(root->right);
    }
}

int qtdLeafs(Node *root){
    if(root == NULL){
        return 0;
    }
    else if(root->left == NULL && root->right == NULL){
        return 1;
    }
    else{
        return qtdLeafs(root->left)+qtdLeafs(root->right);
    }
}

int maior(int a,int b){
    return (a>b) ? a :b;
}

int altura(Node *root){
    if(root == NULL){
        return -1;
    }
    int Dir = altura(root->right);
    int Esq = altura(root->left);
    return maior(Dir,Esq)+1;
}

int fb(Node *root){
    if(root){
        return (altura(root->left)-altura(root->right));
    }
    return 0;
}

int main(void){
    int i;
    int array[14]={34,84,15,0,2,99,79,9,88,89,18,31,39,100};
    Node *root = NULL;

    for(i=0 ; i<14 ; i++){
        root = insert(root, array[i]);
        printf("inserted: %d\n", array[i]);
    }

    Node *temp = search(root, 0);
    if(temp){
        printf("Found: %d\n", temp->data);
    }
    else{
        printf("Not found the number\n");
    }

    printf("\nInorder traversal: ");
    inorder_traversal(root);

    return 0;
}