#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída
#include <stdlib.h> // Inclui a biblioteca padrão com funções gerais, incluindo atoi e EXIT_FAILURE/SUCCESS
#include <string.h> // Inclui a biblioteca de manipulação de strings (para strtok, embora não diretamente usada neste código).


int main() {
    // Ponteiros para os arquivos de entrada e saída
    FILE *fp_in = fopen("lists.txt", "r"); // Abre lists.txt para leitura ("r")
    FILE *fp_out = fopen("saida.txt", "w"); // Abre saida.txt para escrita ("w"), sobrescrevendo se existir

    // Verifica se os arquivos foram abertos com sucesso
    if (fp_in == NULL || fp_out == NULL) {
        printf("Arquivos não podem ser abertos.\n"); // Mensagem de erro para o usuário
        return EXIT_FAILURE; // Retorna um código de erro indicando falha
    }

    char line[255]; // Buffer para armazenar cada linha lida do arquivo
    const char comma[] = ","; // Delimitador para separar os números (vírgula)
    char *slice; // Ponteiro para apontar para cada número separado na linha

    // Loop para ler cada linha do arquivo de entrada
    while (fgets(line, 255, fp_in) != NULL) { // fgets lê uma linha do arquivo até 254 caracteres ou \n
        // strtok: (1) não é thread-safe (2) modifica a string original
        slice = strtok(line, comma); // Separa a primeira parte da linha usando a vírgula como delimitador
        int soma = 0; // Inicializa a soma para cada linha
        int value; // Variável para armazenar o valor numérico de cada parte separada
        char text[20]; // Buffer para armazenar a soma formatada como string

        // Loop para processar cada número na linha
        while (slice != NULL) {
            value = atoi(slice); // Converte a string (número) para inteiro
            soma = soma + value; // Acumula a soma
            slice = strtok(NULL, comma); // Obtém o próximo número separado pela vírgula
        }
        //printf("soma: %d ", soma); // linha para debug
        sprintf(text, "%d\n", soma); // Formata a soma como string, adicionando uma nova linha
        //sprintf(text, "%s%s",text, "\n"); // alternativa sem sprintf
        //printf("texto: %s", text); // linha para debug

        fputs(text, fp_out); // Escreve a soma formatada no arquivo de saída
    }

    fclose(fp_in); // Fecha o arquivo de entrada
    fclose(fp_out); // Fecha o arquivo de saída
    return EXIT_SUCCESS; // Retorna um código de sucesso
}