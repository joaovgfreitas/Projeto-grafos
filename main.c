#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int main(int argc, char *argv[]) {
    FILE *file;
    int i = 0, j = 0, numVertices;
    char arquivo[30], frase[MAX];

    printf("Digite o nome do arquivo que deseja ler ou SAIR para terminar o programa: ");
    scanf("%s", arquivo);

    while (strcmp(arquivo, "SAIR") != 0) {
        snprintf(arquivo, sizeof(arquivo), "%s.txt", arquivo); // Adiciona .txt ao final do nome escrito pelo usuário
        file = fopen(arquivo, "r"); // Carrega o arquivo

        if (file == NULL) { // Checa se o arquivo carregado é válido
            printf("Nao foi possivel abrir arquivo.");
            return 1;
        }
		
		numVertices = 0;//Reinicia o contador de vertices
        while (fgets(frase, MAX, file) != NULL) { // Percorre linha por linha do txt
            numVertices++; // Contagem do número de vértices
        }

        fclose(file); // Fecha o arquivo

        // Reabre o arquivo para ler a matriz do inicío
        file = fopen(arquivo, "r");
        if (file == NULL) {
            printf("Nao foi possivel abrir arquivo.");
            return 1;
        }

        int matriz[numVertices][numVertices];//Declaração da matriz
        for (i = 0; i < numVertices; i++) {
            for (j = 0; j < numVertices; j++) {
                fscanf(file, "%i", &matriz[i][j]);//Lê caracter por caracter e escreve na matriz de inteiros;
                printf("%i ", matriz[i][j]);
            }
            printf("\n");
        }
		fclose(file); // Fecha o arquivo
		
		

        printf("\nDigite o nome do arquivo que deseja ler ou SAIR para terminar o programa: ");
        scanf("%s", arquivo);
    }

    printf("\nSaindo...\n");
    return 0;
}

