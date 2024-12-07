#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída
#include <stdlib.h> // Inclui a biblioteca padrão com funções gerais, incluindo atof
#include <string.h> // Inclui a biblioteca de manipulação de strings
#include <math.h> // Inclui a biblioteca math.h para funções matemáticas, incluindo sqrt e pow
#define MaxCaractersLinha 1000


// struct para armazenar coordenadas
typedef struct coordenada {
    float x;
    float y;
    char point[50];
    float distanceToOrigin;
}coordenada;

// Função para calcular a menor distância euclidiana entre dois pontos
float euclidianDistance(coordenada coord, coordenada coord2) {
    float distance = 0.0;
    distance = sqrt(pow(coord2.x - coord.x, 2) + pow(coord2.y - coord.y, 2));
    return distance;
}

// Função para calcular a distância euclidiana total
float totalEuclidianDistance(coordenada coord[], int quantCoordenadas) {
    float distance = 0.0;
    for( int i = 0; i < quantCoordenadas-1; i++) {
        distance += euclidianDistance(coord[i+1], coord[i]);
    }
    return distance;
}

// Função para converter o array de coordenadas em string
void coordPointsToString(coordenada coord[], int quantCoordenadas, char str[]) {
    for (int i = 0; i < quantCoordenadas; i++) {
        strcat(str, coord[i].point); // concatena os valores da struct coordenada em uma string
        strcat(str, " "); // concatena um " " após o ponto
    }
}

// mergeSort para organizar lista de pontos

int main()
{
    // Ponteiros para os arquivos de entrada e saída
    FILE *fp_in = fopen("L0Q1.in", "r"); // Abre o arquivo de leitura ("r")
    FILE *fp_out = fopen("L0Q1.out", "w"); // Abre o arquivo de escrita ("w")

    if (fp_in == NULL || fp_out == NULL) // Tratamento de erro
    {
        printf("Files cannot be oppened");
        return EXIT_FAILURE;
    }

    coordenada coord[100]; // Buffer para armazenar as coordenadas (points)
    char line[MaxCaractersLinha]; // Buffer para armazenar cada linha lida do arquivo
    char stringCoords[MaxCaractersLinha]; // Buffer para armazenar a array de coordenadas formatada como string

    const char space[] = " ";
    const char points_separators[] = "(,)";
    //char *outer_context;
    //char *inner_context;

    while (fgets(line, sizeof(line), fp_in) != NULL)
    {
        int contCoords=0; // Contador para armazenar o número de pontos na linha
        // char text[MaxCaractersLinha]; // Buffer para armazenar a saída formatada como string

        char *slice = strtok(line, space);
        while (slice != NULL)
        {
            if(slice[0] == '(' && slice[strlen(slice)-1] == ')') {
                // armazenar ponto na struct (ponto atual)
                strcpy(coord[contCoords].point,slice); //

                // armazena o x e o y daquela coordenada

                sscanf(slice, "(%f,%f)", &coord[contCoords].x, &coord[contCoords].y);

                // if (sscanf(slice, "(%f,%f)", &coord[contCoords].x, &coord[contCoords].y) == 2) { // DEBUG
                //     printf("x = %.2f, y = %.2f\n", coord[contCoords].x, coord[contCoords].y);
                // } else {
                //     printf("Erro ao interpretar a string.\n"); // DEBUG
                // }

                // calcula distância para origem
                coord[contCoords].distanceToOrigin = sqrt(pow(coord[contCoords].x, 2) + pow(coord[contCoords].y, 2)); // Calcula a distância daquele ponto para ao ponto (0,0)

                // Aumenta o contador, contabilizando coordenada atual
                contCoords++;
            }
            slice = strtok(NULL, space);
        }


        // calcular a distância total euclidiana
        float distance = 0.0;
        if(contCoords >= 2){ //calcula apenas caso hajam ao menos dois pontos listados na linha
            distance = totalEuclidianDistance(coord, contCoords);
        }

        // calcular a menor distância entre o primeiro e o ultimo ponto da entrada
        float shortcut = 0.0;
        if(contCoords >= 2){ //calcula apenas caso hajam ao menos dois pontos listados na linha
            shortcut= euclidianDistance(coord[contCoords-1], coord[0]);
        }

        // ordenar array de coordenadas pela distância até a origem (coord.distanceToOrigin)
        

        // converter o array de coordenadas em uma string
        coordPointsToString(coord, contCoords, stringCoords);

        // formatação impressão da linha de saída
        char text[MaxCaractersLinha];
        sprintf(text, "points %sdistance %.2f shortcut %.2f\n",stringCoords,distance,shortcut) ; // Formata a saída como string, adicionando uma nova linha
        fputs(text, fp_out);
        // fprintf(fp_out, "points %s distance %.2f shortcut %.2f\n",stringCoords,distance,shortcut);
    }

    fclose(fp_in);
    fclose(fp_out);
    return EXIT_SUCCESS;

}