// Integrantes da equipe: Ana Emilia Lobo e Martfeld Mutim (20241160001) Marcus Vinicius Silva da Fonseca (20241160005) e Roberto Silva Barreto (20241160031)

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
        char textOut[MaxCaractersLinha]=""; // Buffer para armazenar o texto de saída para uma linha
        char textAux[50]; // Buffer auxiliar para armazenar o texto concatenado na string de saída
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

            // Imprimir na linha o número de pops, se houveram
            if(contPop>0){ // Realizado apenas quando hover alteração de ordem na pilha principal
                // printf("%dx-pop ",contPop); //DEBUG
                sprintf(textAux,"%dx-pop ",contPop); // salva na strig auxiliar o número de pops realizados (armazenados em contPop)
                // printf("\n|textAux: %s ",textAux); //DEBUG
                strcat(textOut,textAux); // concatena a string auxiliar no texto de saída
                // printf("|textOut: %s|\n",textOut); //DEBUG
            }

            // Imprimir na linha o push realizado
            push(&p,slice); // Insere o primeiro nome na pilha principal ADD
            // printf("push-%s ",p.top->nome); //DEBUG
            sprintf(textAux,"push-%s ",p.top->nome); // salva na strig auxiliar o push realizado
            // printf("\n|textAux: %s ",textAux); //DEBUG
            strcat(textOut,textAux); // concatena a string auxiliar no texto de saída
            // printf("|textOut: %s|\n",textOut); //DEBUG
            

            while(auxP.top!=NULL){ // Varre a pilha auxiliar por completo, copiando os elementos para pilha principal
                auxPop = pop(&auxP);
                push(&p,auxPop->nome);

                // Imprimir na linha cada push realizado após a reordenação
                // printf("push-%s ",auxPop->nome); //DEBUG
                sprintf(textAux,"push-%s ",auxPop->nome); // salva na strig auxiliar o push realizado
                // printf("\n|textAux: %s ",textAux); //DEBUG
                strcat(textOut,textAux); // concatena a string auxiliar no texto de saída
                // printf("|textOut: %s|\n",textOut); //DEBUG
            }
            slice = strtok(NULL, space); // Avança para o próximo nome na linha
        }

        // printf("p.top: %s\n",p.top); //DEBUG
        // imprimir_pilha(&p); //DEBUG
        // printf("textOut: %s",textOut); //DEBUG

        // Imprimir linha no arquivo
        printf("%s",textOut);
        fputs(textOut,fp_out); // Insere o texto de saída da linha no arquivo
        
        if (feof(fp_in))// Verifica se a leitura chegou ao fim do arquivo
        {
            break;
        }
        else{
             printf("\n"); //DEBUG
             fputs("\n",fp_out); // Insere "\n" no arquivo de saída caso haja próxima linha
        }
    }

    fclose(fp_in);
    fclose(fp_out);
    return EXIT_SUCCESS;
}