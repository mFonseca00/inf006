#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída
#include <stdlib.h> // Inclui a biblioteca padrão com funções gerais, incluindo atof
#include <string.h> // Inclui a biblioteca de manipulação de strings


#define MaxCaractersLinha 1000 // Define o tamanho máximo de uma linha lida do arquivo de entrada


// definição da struct para cada nó de uma lista
typedef struct reg{
    int valor;
    struct reg *prox;
}No;

// definição da struct para armazenar início da lista, a soma dos seus valores e seu tamanho
typedef struct {
    No *inicio;
    int tam;
    int soma;
}lista;

// Função para criar uma nova lista
lista* criarLista(){
    lista *novaLista = (lista*) malloc(sizeof(lista));
    novaLista->inicio = NULL;
    novaLista->tam = 0;
    novaLista->soma = 0;

    return novaLista; // Retorna o ponteiro da nova lista para ser adicionado no array
}

// Função para inserir novo elemento na lista de forma ordenada
void inserirOrdenadoLista(lista *lista, int elemento){
    No *aux, *novo = malloc(sizeof(No));
    if(novo){
        lista->tam++;
        lista->soma += elemento;
        novo->valor = elemento;
        // A lista está vazia?
        if(lista->inicio == NULL){
            novo->prox = NULL;
            lista->inicio = novo;
        }
        // É o menor elemento?
        else if(novo->valor < lista->inicio->valor){
            novo->prox = lista->inicio;
            lista->inicio = novo;
        }
        else{
            aux = lista->inicio;
            // Percorre a lista enquanto o valor a ser adicionado for maior que o próximo da lista
            while(aux->prox && novo->valor > aux->prox->valor){
                aux = aux->prox; // Enquanto for maior, atualiza o valor do aux
            }
            novo->prox = aux->prox;
            aux->prox = novo;
        }
    }
    else{
        printf("Erro ao alocar memória para novo nó.\n");
    }
}

// Função para imprimir listas utilizada para debug do código
void printLista(lista *lista){
    No *atual = lista->inicio;
    while(atual != NULL){
        printf("%d ", atual->valor);
        atual = atual->prox;
    }
    printf("\tTamanho: %d\tSoma: %d",lista->tam, lista->soma);
    printf("\n");
}

// Função para loiberar espaço de memória ocupado por uma lista
void freeLista (lista *lista){
    No *atual = lista->inicio;
    while( atual != NULL){
        No *aux = atual;
        atual = atual->prox;
        free(aux);
    }
    free(lista);
}

// Quicksort para ordenar listas com base na soma de seus elementos
void trocar(lista **a, lista **b){ //troca dois ponteiros de lista
    lista *temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(lista **arr, int esq, int dir){
    lista *pivot = arr[dir]; //pivot escolhido como ultimo elemento (ultima lista)
    int i = (esq-1);
    for(int j = esq; j<=dir - 1; j++){
        //verifica se a soma da lista atual é menor ou igual à soma da lista pivot
        if(arr[j]->soma <= pivot->soma){
            i++;
            trocar(&arr[i],&arr[j]);
        }
    }
    trocar(&arr[i+1],&arr[dir]);
    return (i+1);
}

void quickSortLista(lista **arr, int esq, int dir){
    if(esq<dir){
        int indexPart = particionar(arr, esq, dir);
        //ordena recursivamente as duas metades do array de listas
        quickSortLista(arr, esq, indexPart-1);
        quickSortLista(arr, indexPart+1, dir);
    }
}


int main(void){
    // Ponteiros para os arquivos de entrada e saída
    FILE *fp_in = fopen("L1Q1.in", "r"); // Abre o arquivo de leitura ("r")
    FILE *fp_out = fopen("L1Q1.out", "w"); // Abre o arquivo de escrita ("w")

    if (fp_in == NULL || fp_out == NULL) // Tratamento de erro
    {
        printf("File cannot be oppened");
        return EXIT_FAILURE;
    }

    
    char line[MaxCaractersLinha]; // Buffer para armazenar cada linha lida do arquivo
    //Separadores
    const char space[] = " ";
    const char start[] = "start";
    int contLinha=0;

     while (fgets(line, sizeof(line), fp_in) != NULL)
    {
        contLinha++;
        line[strcspn(line, "\n")] = 0; // Remove o \n do final da string para evitar bug
        char *slice = strtok(line, space);
        // printf("\n\nNova linha\n"); // DEBUG

        lista **arrListas = NULL; //array para armazenar as listas da linha (inicialmente aponta para NULL)
        int tamArrListas=0; // Tamanho do array de listas
        int listaAtual=0; // Posição atual a ser preenchida no array de listas


        //Separar os inteiros da lista com base no espaço
        while(slice!=NULL){
            char elemento[] = "start";
            int inteiro;
            // Obtém o elemento da lista de inteiros
            strcpy(elemento,slice);

            // Verifica se o elemento obtido é o marcador de início de lista (start) ou um elemento da lista
            if(strcmp(slice, start) == 0){
                // printf("\nLista:\n"); // DEBUG
                //Verifica se é necessário realocar o array
                if(listaAtual>=tamArrListas){
                    tamArrListas++;
                    arrListas = (lista **)realloc(arrListas, tamArrListas * sizeof(lista *)); // realoca o array de listas
                    if(arrListas == NULL){
                        printf("Falha na realocacao de memoria.\n"); // DEBUG
                        return EXIT_FAILURE;
                    }
                }
                // Cria a nova lista e insere seu ponteiro na array
                arrListas[listaAtual]=criarLista();
                if(arrListas[listaAtual] == NULL){
                    printf("Erro ao alocar memoria para nova lista.\n"); // DEBUG
                    return EXIT_FAILURE;
                }
                // printf("Nova lista criada, lista atual: %d.\n", listaAtual); // DEBUG
                listaAtual++; // incrementa lista atual (index)
            }
            else{
                if(listaAtual > 0){
                    inteiro = atoi(elemento);
                    // printf("Elemento obtido: %d\n",inteiro); // DEBUG

                    // insere o elemento na lista atual (já ordenando), atualizando a soma dos elementos dela
                    inserirOrdenadoLista(arrListas[listaAtual-1], inteiro);
                }
                else{
                    printf("Erro: lista nao alocada\n"); // DEBUG
                }
            }
            slice = strtok(NULL, space); // Avança para o próximo número na lista
        }

        printf("\n----------------------------Listas da linha %d----------------------------\n\n", contLinha); //DEBUG
        for(int i = 0; i<tamArrListas; i++){ //DEBUG
            printf("Lista %d: ",i); //DEBUG
            printLista(arrListas[i]); //DEBUG
        }

        // Ordena de forma crescente as listas com base na soma de seus elementos (quicksort em arrListas com base em lista->soma)
        quickSortLista(arrListas,0, tamArrListas-1);
        printf("Listas ordenadas de forma crescente:\n"); //DEBUG
        for(int i = 0; i<tamArrListas; i++){ //DEBUG
            printf("Lista %d: ",i); //DEBUG
            printLista(arrListas[i]); //DEBUG
        }

        // Converte as listas em uma string


        // Formatação para impressão da linha de saída


        // Libera o espaço ocupado na memória
        // printf("\nIniciando exclusao das listas da linha %d\n", contLinha); // DEBUG
        for(int i = 0; i<tamArrListas; i++){
            // printf("Excluindo lista %d\n", i); // DEBUG
            freeLista(arrListas[i]);
        }
        free(arrListas);
        arrListas = NULL;
    }

    fclose(fp_in);
    fclose(fp_out);
    return EXIT_SUCCESS;
}