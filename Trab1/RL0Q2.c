#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MaxCaractersLinha 1000

// Estrutura para armazenar coordenadas
typedef struct coordenada {
    float x;
    float y;
    float distanceToOrigin;
    char point[50];
} coordenada;

// Função para calcular a distância euclidiana entre um ponto e a origem
float distanceToOrigin(coordenada coord) {
    return sqrt(pow(coord.x, 2) + pow(coord.y, 2));
}

// Funções auxiliares para ordenação
void swapStrings(char *a, char *b) {
    char temp[100];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

void swapIntegers(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapFloats(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

void swapCoordinates(coordenada *a, coordenada *b) {
    coordenada temp = *a;
    *a = *b;
    *b = temp;
}

// Função para ordenar strings alfabeticamente
void sortStrings(char arr[][100], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[i], arr[j]) > 0) {
                swapStrings(arr[i], arr[j]);
            }
        }
    }
}

// Função para ordenar inteiros
void sortIntegers(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                swapIntegers(&arr[i], &arr[j]);
            }
        }
    }
}

// Função para ordenar floats
void sortFloats(float arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                swapFloats(&arr[i], &arr[j]);
            }
        }
    }
}

// Função para ordenar coordenadas pela distância à origem
void sortCoordinates(coordenada arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i].distanceToOrigin > arr[j].distanceToOrigin) {
                swapCoordinates(&arr[i], &arr[j]);
            }
        }
    }
}

int main() {
    FILE *fp_in = fopen("L0Q2.in", "r");
    FILE *fp_out = fopen("L0Q2.out", "w");

    if (fp_in == NULL || fp_out == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return EXIT_FAILURE;
    }

    char line[MaxCaractersLinha];
    while (fgets(line, sizeof(line), fp_in)) {
        line[strcspn(line, "\n")] = 0; // Remove o '\n'

        char strings[100][100];
        int integers[100], intCount = 0, stringCount = 0, floatCount = 0, coordCount = 0;
        float floats[100];
        coordenada coords[100];

        char *token = strtok(line, " ");
        while (token) {
            if (sscanf(token, "(%f,%f)", &coords[coordCount].x, &coords[coordCount].y) == 2) {
                strcpy(coords[coordCount].point, token);
                coords[coordCount].distanceToOrigin = distanceToOrigin(coords[coordCount]);
                coordCount++;
            } else if (strspn(token, "0123456789-") == strlen(token)) {
                integers[intCount++] = atoi(token);
            } else if (strspn(token, "0123456789.-") == strlen(token)) {
                floats[floatCount++] = atof(token);
            } else {
                strcpy(strings[stringCount++], token);
            }
            token = strtok(NULL, " ");
        }

        sortStrings(strings, stringCount);
        sortIntegers(integers, intCount);
        sortFloats(floats, floatCount);
        sortCoordinates(coords, coordCount);

        // Formatar a saída
        fprintf(fp_out, "str:");
        for (int i = 0; i < stringCount; i++) {
            fprintf(fp_out, " %s", strings[i]);
        }

        fprintf(fp_out, " int:");
        for (int i = 0; i < intCount; i++) {
            fprintf(fp_out, " %d", integers[i]);
        }

        fprintf(fp_out, " float:");
        for (int i = 0; i < floatCount; i++) {
            fprintf(fp_out, " %.2f", floats[i]);
        }

        fprintf(fp_out, " p:");
        for (int i = 0; i < coordCount; i++) {
            fprintf(fp_out, " %s", coords[i].point);
        }

        fprintf(fp_out, "\n");
    }

    fclose(fp_in);
    fclose(fp_out);
    return EXIT_SUCCESS;
}
