#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main (void){
    // Ponteiros para os arquivos de entrada e saída
    FILE *fp_in = fopen("L1Q3.in", "r"); // Abre o arquivo de leitura ("r")
    FILE *fp_out = fopen("L1Q3.out", "w"); // Abre o arquivo de escrita ("w")

    if (fp_in == NULL || fp_out == NULL) // Tratamento de erro
    {
        printf("File cannot be oppened");
        return EXIT_FAILURE;
    }

    


}