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
// void inserirListaOrdenada(lista *lista, int elemento){
//     No *novo = malloc(sizeof(No));
//     if(novo){
//         lista->tam++;
//         lista->soma+=elemento;

//     }
//     else{
//         printf("Erro ao alocar memória para novo nó.\n");
//         return EXIT_FAILURE;
//     }
// }

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

     while (fgets(line, sizeof(line), fp_in) != NULL)
    {

        char *slice = strtok(line, space);
        printf("\nNova linha\n"); // DEBUG

        lista **arrListas = NULL; //array para armazenar as listas da linha (inicialmente aponta para NULL)
        int tamArrListas=0; // Tamanho do array de listas
        int listaAtual=0; // Posição atual a ser preenchida no array de listas


        //Separar os inteiros da lista com base no espaço
        while(slice!=NULL){

            // Declaração de variáveis internas para aquela linha
            char elemento[] = "start";
            int inteiro;
        
            // Obtém o elemento da lista de inteiros
            strcpy(elemento,slice);

            // Verifica se o elemento obtido é o marcador de início de lista (start) ou um elemento da lista
            if(strcmp(slice, start) == 0){
                printf("\nLista:\n"); // DEBUG
                //Verifica se é necessário realocar o array
                if(listaAtual>=tamArrListas){
                    tamArrListas = (tamArrListas == 0) ? 1 : tamArrListas*2; // caso o tam seja 0, aumenta para 1, caso contrário, dobra
                    arrListas = (lista**) realloc(arrListas, tamArrListas * sizeof(lista*)); // realoca o array de listas
                    if(arrListas == NULL){
                        printf("Falha na realocação de memória.\n"); // DEBUG
                        return EXIT_FAILURE;
                    }
                }
                // Cria a nova lista e insere seu ponteiro na array
                arrListas[listaAtual]=criarLista();
                if(arrListas[listaAtual] == NULL){
                    printf("Erro ao alocar memória para nova lista.\n"); // DEBUG
                    return EXIT_FAILURE;
                }
                printf("Nova lista criada.\n"); // DEBUG
            }
            else{
                inteiro=atoi(elemento);
                printf("Elemento obtido: %d\n",inteiro); // DEBUG

                // Salva o elemento na lista atual (já ordenando), atualizando a soma dos elementos dela
            }
            

            slice = strtok(NULL, space); // Avança para o próximo número na lista
        }
        
        // Ordena de forma crescente as listas com base na soma de seus elementos

        // Converte as listas em uma string

        // Formatação para impressão da linha de saída

        // char text[MaxCaractersLinha];
        // sprintf(text, "points %s distance %.2f shortcut %.2f\n",stringCoords,distance,shortcut) ; // Formata a saída como string, adicionando uma nova linha
        // fputs(text, fp_out);
    }

    fclose(fp_in);
    fclose(fp_out);
    return EXIT_SUCCESS;
}