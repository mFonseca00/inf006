#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída
#include <stdlib.h> // Inclui a biblioteca padrão com funções gerais, incluindo atoi e EXIT_FAILURE/SUCCESS
#include <string.h> // Inclui a biblioteca de manipulação de strings (para strtok, embora não diretamente usada neste código).
#include <math.h> // Inclui a biblioteca math.h para funções matemáticas, incluindo sqrt e pow
#define MaxCaractersLinha 500
#define MaxCoordenadas 200

typedef struct coordenada {
    float x;
    float y;
    char point[50];
    float distanceToOrigin;
}coordenada;

void removeCaractere(char str[],char charToRemove) {
    char temp[strlen(str)];
    int cont=0;
    for ( int i = 0; i < strlen(str); i++) {
        if (str[i] != charToRemove) {
            temp[i] = str[i];
            cont++;
        }
    }
    temp[cont] = '\0';
    strcpy(str, temp);
}

float totalEuclidianDistance(coordenada coord[], int quantCoordenadas) {
    float distance = 0;

    //lógica para calcular a distância euclidiana total

    return distance;
}

float minorEuclidianDistance(coordenada coord[], int quantCoordenadas) {
    float distance = 0;

    //lógica para calcular a menor distância euclidiana entre o primeiro e o ultimo ponto (coord[0] e coord[quantCoordenadas-1])

    return distance;
}

void ordenarCoordenadas(coordenada coord[], int quantCoordenadas) {
    //lógica para ordenar o array de coordenadas pela distância à origem (coord.distanceToOrigin)
}

void pointsToString(coordenada coord[], int quantCoordenadas, char str[]) {
    //lógica para converter o array de coordenadas em uma string
}


int main() {
    // Ponteiros para os arquivos de entrada e saída
    FILE *fp_in = fopen("lists.txt", "r"); // Abre lists.txt para leitura ("r")
    FILE *fp_out = fopen("saida.txt", "w"); // Abre saida.txt para escrita ("w"), sobrescrevendo se existir

    // Verifica se os arquivos foram abertos com sucesso
    if (fp_in == NULL || fp_out == NULL) {
        printf("Arquivos não podem ser abertos.\n"); // Mensagem de erro para o usuário
        return EXIT_FAILURE; // Retorna um código de erro indicando falha
    }

    char line[MaxCaractersLinha]; // Buffer para armazenar cada linha lida do arquivo
    coordenada coord[MaxCoordenadas]; // Buffer para armazenar cada coordenada lida do arquivo
    const char delimitatorPoint[] = " "; // Delimitador para separar os pontos
    const char delimitatorCoordinatesX[] = ","; // Delimitador para separar as coordenadas (x e y)
    const char delimitatorCoordinatesY[] = ")"; // Delimitador para separar as coordenadas (x e y)
    char *slice; // Ponteiro para apontar para cada pomto separado na linha
    char *slice2; // Ponteiro para apontar para cada número separado na linha

    // Loop para ler cada linha do arquivo de entrada
    while (fgets(line, MaxCaractersLinha, fp_in) != NULL) { // fgets lê uma linha do arquivo até 500 caracteres ou \n
        // strtok: (1) não é thread-safe (2) modifica a string original
        slice = strtok(line, delimitatorPoint); // Separa a primeira parte da linha usando o espaço como delimitador
        int cont=0; // Contador para armazenar o número de pontos na linha
        char text[MaxCaractersLinha]; // Buffer para armazenar a saída formatada como string
        
        // Loop para processar cada ponto na linha
        while (slice != NULL) {
            coord[cont].point = slice;
            
            slice2 = strtok(slice, delimitatorCoordinatesX); // Separa o primeiro valor do ponto usando a vírgula como delimitador
            removeCaractere(slice2, '('); // Remove o caractere "( para que seja feita a conversão para float" 
            coord[cont].x = atof(slice2); // Converte a string (número) para float e armazena o valor de x

            slice2 = strtok(NULL, delimitatorCoordinatesY); // Separa o segundo valor do ponto usando o ")" como delimitador
            coord[cont].y = atof(slice2); // Converte a string (número) para float e armazena o valor de y

            coord[cont].distanceToOrigin = sqrt(pow(coord[cont].x, 2) + pow(coord[cont].y, 2)); // Calcula a distância daquele ponto para ao ponto (0,0)
            cont++;

            slice = strtok(NULL, delimitatorPoint); // Obtém o próximo ponto separado pelo espaço
        }

        //calcular a distância total euclidiana
        float distance = totalEuclidianDistance(coord, cont);

        //calcular a menor distância entre o primeiro e o ultimo ponto da entrada

        float shortcut = minorEuclidianDistance(coord, cont);

        //ordenar array de coordenadas pela distância até a origem (coord.distanceToOrigin)

        ordenarCoordenadas(coord, cont);

        //converter o array de coordenadas em uma string

        char stringCoords[MaxCaractersLinha];
        pointsToString(coord, cont, stringCoords);

        //formatação da linha de saída
        sprintf(text, "points %s distance %.2f shortcut %.2f\n",stringCoords,distance,shortcut) ; // Formata a saída como string, adicionando uma nova linha
 

        fputs(text, fp_out); // Escreve a soma formatada no arquivo de saída
    }

    fclose(fp_in); // Fecha o arquivo de entrada
    fclose(fp_out); // Fecha o arquivo de saída
    return EXIT_SUCCESS; // Retorna um código de sucesso
}