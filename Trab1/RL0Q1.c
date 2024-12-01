#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_CARACTERES_LINHA 500
#define MAX_COORDENADAS 100

// struct para armazenar coordenadas
typedef struct coordenada {
    float x;
    float y;
    char *point; // Ponteiro para string, alocação dinâmica
    float distanceToOrigin;
} Coordenada;

// Função para calcular a distância euclidiana entre dois pontos
float euclidianDistance(const Coordenada coord1, const Coordenada coord2) {
    return sqrt(pow(coord1.x - coord2.x, 2) + pow(coord1.y - coord2.y, 2));
}

// Função para calcular a distância euclidiana total
float totalEuclidianDistance(const Coordenada coord[], int quantCoordenadas) {
    float totalDistance = 0.0;
    for (int i = 0; i < quantCoordenadas - 1; i++) {
        totalDistance += euclidianDistance(coord[i], coord[i + 1]);
    }
    return totalDistance;
}

// Função auxiliar merge para o merge sort
void mergeCoords(Coordenada coord[], int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    Coordenada *esq = (Coordenada *)malloc(n1 * sizeof(Coordenada));
    Coordenada *dir = (Coordenada *)malloc(n2 * sizeof(Coordenada));

    for (int i = 0; i < n1; i++) {
        esq[i] = coord[inicio + i];
    }
    for (int i = 0; i < n2; i++) {
        dir[i] = coord[meio + 1 + i];
    }

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (esq[i].distanceToOrigin <= dir[j].distanceToOrigin) {
            coord[k++] = esq[i++];
        } else {
            coord[k++] = dir[j++];
        }
    }

    while (i < n1) {
        coord[k++] = esq[i++];
    }
    while (j < n2) {
        coord[k++] = dir[j++];
    }

    free(esq);
    free(dir);
}

// Função para ordenar, através do merge sort, o array de coordenadas com relação à distância à origem
void mergeSortCoords(Coordenada coord[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSortCoords(coord, inicio, meio);
        mergeSortCoords(coord, meio + 1, fim);
        mergeCoords(coord, inicio, meio, fim);
    }
}

// Função para converter o array de coordenadas em string (com alocação dinâmica)
char* coordPointsToString(const Coordenada coord[], int quantCoordenadas) {
    char *str = (char*)malloc(MAX_CARACTERES_LINHA * sizeof(char)); // Alocação dinâmica!
    str[0] = '\0'; // Inicializa a string
    for (int i = 0; i < quantCoordenadas; i++) {
        char *temp = (char*)malloc((strlen(coord[i].point) + 1) * sizeof(char));
        strcpy(temp, coord[i].point);
        strcat(str, temp);
        free(temp); // Libera memória do buffer temporário
    }
    return str;
}

int main() {
    FILE *fp_in = fopen("lists.txt", "r");
    FILE *fp_out = fopen("saida.txt", "w");

    if (fp_in == NULL || fp_out == NULL) {
        printf("Erro ao abrir arquivos");
        return EXIT_FAILURE;
    }

    char line[MAX_CARACTERES_LINHA];
    Coordenada coord[MAX_COORDENADAS];
    const char delimitatorPoint[] = " ";
    const char delimitatorCoordinatesX[] = ","; // delimitador para X
    const char delimitatorCoordinatesY[] = ")"; // delimitador para Y
    char *slice;
    char *endptr; // auxiliar para atof
    int contCoords = 0;
    char *stringCoords;

    while (fgets(line, MAX_CARACTERES_LINHA, fp_in) != NULL) {
        slice = strtok(line, delimitatorPoint);
        contCoords = 0;

        while (slice != NULL && contCoords < MAX_COORDENADAS) {
            coord[contCoords].point = strdup(slice); // alocação dinâmica e copia da string

            char *x_str = strtok(NULL, delimitatorCoordinatesX);
            char *y_str = strtok(NULL, delimitatorCoordinatesY);

            coord[contCoords].x = atof(x_str);

            coord[contCoords].y = atof(y_str);

            coord[contCoords].distanceToOrigin = sqrt(pow(coord[contCoords].x, 2) + pow(coord[contCoords].y, 2));
            contCoords++;
            slice = strtok(NULL, delimitatorPoint);
        }

        float totalDistance = (contCoords >= 2) ? totalEuclidianDistance(coord, contCoords) : 0.0;
        float shortcut = (contCoords >= 2) ? euclidianDistance(coord[0], coord[contCoords - 1]) : 0.0;

        mergeSortCoords(coord, 0, contCoords - 1);
        stringCoords = coordPointsToString(coord, contCoords);

        char text[MAX_CARACTERES_LINHA]; // aumenta o tamanho
        sprintf(text, "points %s distance %.2f shortcut %.2f\n", stringCoords, totalDistance, shortcut);
        fputs(text, fp_out);

        // Libera memória alocada para as strings que armazenam point
        for (int i = 0; i < contCoords; i++) {
            free(coord[i].point);
        }
        free(stringCoords);
    }

    fclose(fp_in);
    fclose(fp_out);
    return EXIT_SUCCESS;
}