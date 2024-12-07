#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída
#include <stdlib.h> // Inclui a biblioteca padrão com funções gerais, incluindo atoi e EXIT_FAILURE/SUCCESS
#include <string.h> // Inclui a biblioteca de manipulação de strings (para strtok, embora não diretamente usada neste código).
#include <math.h> // Inclui a biblioteca math.h para funções matemáticas, incluindo sqrt e pow
#define MaxCaractersLinha 1000


// struct para armazenar coordenadas
typedef struct coordenada {
    float x;
    float y;
    char point[50];
    float distanceToOrigin;
}coordenada;

