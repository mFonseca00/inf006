#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Tamanho máximo da pilha
#define MAX_Nome 50 // Tamanho máximo do nome

typedef struct {
    char stack[MAX][MAX_Nome];
    int top;
} Pilha;

void init(Pilha *p) {
    p->top = -1;
}

int isEmpty(Pilha *p) {
    return p->top == -1;
}

int isFull(Pilha *p) {
    return p->top == MAX - 1;
}

void printStack(Pilha *p) {
    printf("Pilha final (ordenada):\n");
    for (int i = 0; i <= p->top; i++) {
        printf("%s\n", p->stack[i]);
    }
}

// Função empilhar
void push(Pilha *p, char *nome, FILE *outFile) {
    char temp[MAX][MAX_Nome];
    int tempCount = 0;  

    while (!isEmpty(p) && strcmp(p->stack[p->top], nome) > 0) {
        strcpy(temp[tempCount++], p->stack[p->top--]);
        fprintf(outFile, "1x-pop\n");
    }

    if (!isFull(p)) {
        strcpy(p->stack[++p->top], nome);
        fprintf(outFile, "push-%s\n", nome);
    }

    for (int i = tempCount - 1; i >= 0; i--) {
        if (!isFull(p)) {
            strcpy(p->stack[++p->top], temp[i]);
            fprintf(outFile, "push-%s\n", temp[i]);
        }
    }
}

void processInput(const char *inputFile, const char *outputFile) {
    Pilha pilha; 
    init(&pilha);
    
    FILE *inFile = fopen(inputFile, "r");
    if (!inFile) {
        perror("Erro ao abrir arquivo de entrada");
        exit(EXIT_FAILURE);
    }

    FILE *outFile = fopen(outputFile, "w");
    if (!outFile) {
        perror("Erro ao abrir arquivo de saída");
        fclose(inFile);
        exit(EXIT_FAILURE);
    }

    char name[MAX_Nome];
    while (fscanf(inFile, "%s", name) != EOF) {
        push(&pilha, name, outFile);
    }

    fclose(inFile);
    fclose(outFile);

    // Imprimir a pilha final após o processamento
     printStack(&pilha);
}

int main() {
    const char *inputFile = "L1Q2.in";
    const char *outputFile = "L1Q2.out";

    processInput(inputFile, outputFile);

    printf("Arquivo de saída gerado com sucesso!\n");

    return 0;
}