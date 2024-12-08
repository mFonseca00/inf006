// Integrantes da dupla: Marcus Vinicius Silva da Fonseca (20241160005) e Roberto Silva Barreto (20241160031)

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


//Funções de ordenação


// Resolver o (Implicit declaration of function)
int partitionStrings(char arr[][100], int low, int high);
int partitionIntegers(int arr[], int low, int high);
int partitionFloats(float arr[], int low, int high);
int partitionCoordinates(coordenada arr[], int low, int high);


// Função para ordenar strings alfabeticamente (Update to Quick Sort)
void quickSortStrings(char arr[][100], int low, int high) {
    if (low < high) {
        int pi = partitionStrings(arr, low, high);
        quickSortStrings(arr, low, pi - 1);
        quickSortStrings(arr, pi + 1, high);
    }
}

int partitionStrings(char arr[][100], int low, int high) {
    char pivot[100];
    strcpy(pivot, arr[high]);
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            swapStrings(arr[i], arr[j]);
        }
    }
    swapStrings(arr[i + 1], arr[high]);
    return (i + 1);
}


// Função para ordenar inteiros (Update to Quick Sort)
void quickSortIntegers(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionIntegers(arr, low, high);
        quickSortIntegers(arr, low, pi - 1);
        quickSortIntegers(arr, pi + 1, high);
    }
}

int partitionIntegers(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swapIntegers(&arr[i], &arr[j]);
        }
    }
    swapIntegers(&arr[i + 1], &arr[high]);
    return (i + 1);
}


// Função para ordenar floats (Update to Quick Sort)
void quickSortFloats(float arr[], int low, int high) {
    if (low < high) {
        int pi = partitionFloats(arr, low, high);
        quickSortFloats(arr, low, pi - 1);
        quickSortFloats(arr, pi + 1, high);
    }
}

int partitionFloats(float arr[], int low, int high) {
    float pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swapFloats(&arr[i], &arr[j]);
        }
    }
    swapFloats(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Função para ordenar coordenadas pela distância à origem (Update to Quick Sort)
void quickSortCoordinates(coordenada arr[], int low, int high) {
    if (low < high) {
        int pi = partitionCoordinates(arr, low, high);
        quickSortCoordinates(arr, low, pi - 1);
        quickSortCoordinates(arr, pi + 1, high);
    }
}

int partitionCoordinates(coordenada arr[], int low, int high) {
    float pivot = arr[high].distanceToOrigin;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j].distanceToOrigin < pivot) {
            i++;
            swapCoordinates(&arr[i], &arr[j]);
        }
    }
    swapCoordinates(&arr[i + 1], &arr[high]);
    return (i + 1);
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

        quickSortStrings(strings, 0, stringCount - 1);
        quickSortIntegers(integers, 0, intCount - 1);
        quickSortFloats(floats, 0, floatCount - 1);
        quickSortCoordinates(coords, 0, coordCount - 1);

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
