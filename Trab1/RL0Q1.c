#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída
#include <stdlib.h> // Inclui a biblioteca padrão com funções gerais, incluindo atoi e EXIT_FAILURE/SUCCESS
#include <string.h> // Inclui a biblioteca de manipulação de strings (para strtok, embora não diretamente usada neste código).
#include <math.h> // Inclui a biblioteca math.h para funções matemáticas, incluindo sqrt e pow
#define MaxCaractersLinha 500
#define MaxCoordenadas 200

// struct para armazenar coordenadas
typedef struct coordenada {
    float x;
    float y;
    char point[50];
    float distanceToOrigin;
}coordenada;

// Função para remover um caractere específico de uma string
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

// Função para calcular a menor distância euclidiana entre dois pontos
float euclidianDistance(coordenada coord, coordenada coord2) {
    float distance = 0.0;
    distance = sqrt(pow(coord.x - coord2.x, 2) + pow(coord.y - coord2.y, 2));
    return distance;
}

// Função para calcular a distância euclidiana total
float totalEuclidianDistance(coordenada coord[], int quantCoordenadas) {
    float distance = 0.0;
    for( int i = 0; i < quantCoordenadas-1; i++) {
        euclidianDistance(coord[i+1], coord[i]);
    }
    return distance;
}

//Função para ordenar o array de coordenadas com relação à distância à origem
void ordenarCoordenadas(coordenada coord[], int quantCoordenadas) {

}

//Função para converter o array de coordenadas em string
void coordPointsToString(coordenada coord[], int quantCoordenadas, char str[]) {
    for (int i = 0; i < quantCoordenadas; i++) {
        strcat(str, coord[i].point); // concatena os valores da struct coordenada em uma string    
    }
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
    const char delimitatorCoordinatesX[] = ","; // Delimitador para separar as coordenadas (x)
    const char delimitatorCoordinatesY[] = ")"; // Delimitador para separar as coordenadas (y)
    char *slice; // Ponteiro para apontar para cada ponto separado na linha
    char *slice2; // Ponteiro para apontar para cada número separado na linha

    // Loop para ler cada linha do arquivo de entrada
    while (fgets(line, MaxCaractersLinha, fp_in) != NULL) { // fgets lê uma linha do arquivo até 500 caracteres ou \n
        // strtok: (1) não é thread-safe (2) modifica a string original
        slice = strtok(line, delimitatorPoint); // Separa a primeira parte da linha usando o espaço como delimitador
        int contCoords=0; // Contador para armazenar o número de pontos na linha
        char text[MaxCaractersLinha]; // Buffer para armazenar a saída formatada como string
        char stringCoords[MaxCaractersLinha]; // Buffer para armazenar a array de coordenadas formatada como string

        // Loop para processar cada ponto na linha
        while (slice != NULL) {
            coord[contCoords].point = slice;
            
            slice2 = strtok(slice, delimitatorCoordinatesX); // Separa o primeiro valor do ponto usando a vírgula como delimitador
            removeCaractere(slice2, '('); // Remove o caractere "( para que seja feita a conversão para float" 
            coord[contCoords].x = atof(slice2); // Converte a string (número) para float e armazena o valor de x

            slice2 = strtok(NULL, delimitatorCoordinatesY); // Separa o segundo valor do ponto usando o ")" como delimitador
            coord[contCoords].y = atof(slice2); // Converte a string (número) para float e armazena o valor de y

            coord[contCoords].distanceToOrigin = sqrt(pow(coord[contCoords].x, 2) + pow(coord[contCoords].y, 2)); // Calcula a distância daquele ponto para ao ponto (0,0)
            contCoords++;

            slice = strtok(NULL, delimitatorPoint); // Obtém o próximo ponto separado pelo espaço
        }

        //calcular a distância total euclidiana
        float distance = 0.0;
        if(contCoords >= 2){ //calcula apenas caso hajam ao menos dois pontos listados na linha
            distance = totalEuclidianDistance(coord, contCoords);
        }

        //calcular a menor distância entre o primeiro e o ultimo ponto da entrada
        float shortcut = 0.0;
        if(contCoords >= 2){ //calcula apenas caso hajam ao menos dois pontos listados na linha
            shortcut= euclidianDistance(coord[contCoords-1], coord[0]);
        }

        //ordenar array de coordenadas pela distância até a origem (coord.distanceToOrigin)
        ordenarCoordenadas(coord, contCoords);

        //converter o array de coordenadas em uma string
        char stringCoords[MaxCaractersLinha];
        coordPointsToString(coord, contCoords, stringCoords);

        //formatação da linha de saída
        sprintf(text, "points %s distance %.2f shortcut %.2f\n",stringCoords,distance,shortcut) ; // Formata a saída como string, adicionando uma nova linha
 

        fputs(text, fp_out); // Escreve a soma formatada no arquivo de saída
    }

    fclose(fp_in); // Fecha o arquivo de entrada
    fclose(fp_out); // Fecha o arquivo de saída
    return EXIT_SUCCESS; // Retorna um código de sucesso
}