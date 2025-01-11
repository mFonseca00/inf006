#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxCaractersLinha 1000
#define MaxNome 30

typedef struct no {
    char nome[MaxNome];
    struct no *prox;
} No;

typedef struct {
    int tam;
    No *top;
} Pilha;

void initPilha(Pilha *p) {
    p->top = NULL;
    p->tam = 0;
}

void push(Pilha *p, char nome[]) {
    No *novo = malloc(sizeof(No));
    if (novo) {
        strcpy(novo->nome, nome);
        novo->prox = p->top;
        p->top = novo;
        p->tam++;
    } else {
        printf("Erro ao alocar memória\n");
    }
}

No *pop(Pilha *p) {
    if (p->top != NULL) {
        No *remove = p->top;
        p->top = remove->prox;
        p->tam--;
        return remove;
    } else {
        printf("Pilha vazia!\n");
        return NULL;
    }
}

void imprimir_pilha(Pilha *p) {
    printf("\n-----PILHA de tamanho: %d-----\n\n", p->tam);
    No *aux = p->top;
    while (aux != NULL) {
        printf("%s\n", aux->nome);
        aux = aux->prox;
    }
    printf("\n------FIM------\n\n");
}

int main(void){

    // Ponteiros para os arquivos de entrada e saída
    FILE *fp_in = fopen("L1Q2.in", "r"); // Abre o arquivo de leitura ("r")
    FILE *fp_out = fopen("L1Q2.out", "w"); // Abre o arquivo de escrita ("w")

    if (fp_in == NULL || fp_out == NULL) // Tratamento de erro
    {
        printf("File cannot be oppened");
        return EXIT_FAILURE;
    }

    char line[MaxCaractersLinha]; // Buffer para armazenar cada linha lida do arquivo
    const char space[] = " "; // Separador entre itens da linha

    Pilha p,auxP;
    
    while (fgets(line, sizeof(line), fp_in) != NULL)
    {
        line[strcspn(line, "\n")] = 0; // Remove o \n do final da string para evitar bug
        char *slice = strtok(line, space); // Obtem o primeiro nome da linha
        // printf("\n\nNova linha\n"); // DEBUG

        initPilha(&p); // Inicializa a pilha principal - pilha a ser ordenada
        initPilha(&auxP); // Inicializa a pilha auxiliar - essa pilha sempre estará ordenada com base na principal
        No *auxPop = NULL; // Nó auxiliar para função Pop

        while(slice!=NULL){
            // printf("Elemento obtido: %s\n",slice); // DEBUG
            
            int contPop = 0; // Variável utilizada para contabilizar as remoçoes realizadas no próximo while

            while(p.top != NULL && strcmp(slice, p.top->nome) < 0){ // caso o nome a ser adicionado deva ficar no final da pilha (ser oprimeiro a ser adicionado)
                // printf("%s deve vir depois de %s\n", p.top->nome, slice); // DEBUG
                auxPop = pop(&p); // Retira o nome do topo da pilha principal(anterior)
                contPop++;
                push(&auxP,auxPop->nome); // Insere o nome removido da outra pilha (anterior) na pilha auxiliar
            }

            if(contPop>0){ // Realizado apenas quando hover alteração de ordem na pilha principal
                printf("%dx-pop ",contPop); //DEBUG
                // Imprimir no arquivo o número de pops realizados (armazenados em contPop)
            }

            push(&p,slice); // Insere o primeiro nome na pilha principal ADD
            printf("push-%s ",p.top->nome); //DEBUG
            // Imprimir no arquivo o push realizado

            while(auxP.top!=NULL){ // Varre a pilha auxiliar por completo, copiando os elementos para pilha principal
                auxPop = pop(&auxP);
                push(&p,auxPop->nome);
                printf("push-%s ",auxPop->nome); //DEBUG
                // Imprimir no arquivo cada push realizado
            }
            
            slice = strtok(NULL, space); // Avança para o próximo nome na linha
            
        }

        // printf("p.top: %s\n",p.top); //DEBUG
        // imprimir_pilha(&p); //DEBUG
        printf("\n"); //DEBUG

        if(slice){
            fprintf(fp_out,"\n"); // Insere "\n" caso haja próxima linha
        }
    }

    fclose(fp_in);
    fclose(fp_out);
    return EXIT_SUCCESS;
}