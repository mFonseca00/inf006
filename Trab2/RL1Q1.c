#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída
#include <stdlib.h> // Inclui a biblioteca padrão com funções gerais, incluindo atof
#include <string.h> // Inclui a biblioteca de manipulação de strings


#define MaxCaractersLinha 1000 // Define o tamanho máximo de uma linha lida do arquivo de entrada

// definição da struct para cada nó de uma lista
typedef struct reg {
    int elemento;
    struct reg *prox;
} No;

int main(void){
    // Ponteiros para os arquivos de entrada e saída
    FILE *fp_in = fopen("L1Q1.in", "r"); // Abre o arquivo de leitura ("r")
    FILE *fp_out = fopen("L1Q1.out", "w"); // Abre o arquivo de escrita ("w")

    if (fp_in == NULL || fp_out == NULL) // Tratamento de erro
    {
        printf("File cannot be oppened");
        return EXIT_FAILURE;
    }

    //inserir buffer para as listas

    char line[MaxCaractersLinha]; // Buffer para armazenar cada linha lida do arquivo

    //Separadores
    const char space[] = " ";
    const char start[] = "start";

     while (fgets(line, sizeof(line), fp_in) != NULL)
    {
        // line[strcspn(line, "\n")] = 0; // Remove o '\n' do final da linha para que o código leia o ultimo elemento
        char *slice = strtok(line, space);
        printf("\nNova linha\n"); // DEBUG

        //Separar os inteiros da lista com base no espaço
        while(slice!=NULL){

            char elemento[] = "start";
            int inteiro;
            // Obtém o elemento da lista de inteiros
            strcpy(elemento,slice);
            // Verifica se o elemento obtido é o marcador de início de lista (start) ou um elemento da lista
            if(strcmp(slice, start) == 0){
                printf("\nLista:\n"); // DEBUG

                // Cria uma nova lista

            }
            else{
                inteiro=atoi(elemento);
                printf("Elemento obtido: %d\n",inteiro); // DEBUG

                // Incrementa a quantidade de elementos naquela lista

                // Salva o elemento na lista atual (já ordenando?)

                // Atualiza a soma dos elementos da lista
            }
            

            slice = strtok(NULL, space); // Avança para o próximo número na lista
        }
        

        // Ordena de forma crescente os elementos de cada lista (Verificar se já foi feito)

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