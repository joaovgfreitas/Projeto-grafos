#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

void charToInt(char matrizChar[MAX][MAX], int matrizInt[MAX][MAX], int tamanho) { //Converte a matriz do tipo char em inteiro. !!!!!ACHO QUE ESTÁ COM ERRO NA HORA DE COMPARAR COM STRCMP!!!!!!
    int i, j;
    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho; j++) {
            if (strcmp(&matrizChar[i][j], "0") == 0) { //Checa se o caracter na matriz é igual 0
                matrizInt[i][j] = 0; //Inseri na matriz de inteiro o 0
                printf("0");
            } else if (strcmp(&matrizChar[i][j], "1") == 0) { //Checa se o caracter na matriz é igual 1
                matrizInt[i][j] = 1; //Inseri na matriz de inteiro o 1
                printf("1");
            }
        }
        //printf("%i", matrizInt[i]);
    }
}

int main(int argc, char *argv[]) {
	FILE *file;
	int  i = 0, j = 0, matrizInt[MAX][MAX];
	char matrizChar[MAX][MAX], arquivo[30], frase[MAX];
	
	printf("Digite o nome do arquivo que deseja ler ou SAIR para terminar o programa: ");
	scanf("%s", arquivo);
	
	while(strcmp(arquivo, "SAIR") != 0){ //Compara o nome do arquivo com SAIR, para sair do programa
		
		snprintf(arquivo, sizeof(arquivo), "%s.txt",arquivo); //Adiciona .txt ao final do nome escrito pelo usuário
		file = fopen(arquivo, "r"); //Carrega o arquivo
			
		if(file == NULL){ //Checa se o arquivo carregado é válido
			printf("Nao foi possivel abrir arquivo.");
			return 1;
		}
	
		while(fgets(frase, MAX, file) != NULL){ //Percorre linha por linha do txt e adiciona cada linha a uma matriz do tipo char
			strcpy(matrizChar[i], frase); //Copia a linha do txt para a matriz
			printf("%s", matrizChar[i]);
			i++;
		}
		
		charToInt(matrizChar, matrizInt, MAX);
	
		fclose(file); //Fecha o arquivo
		printf("\n\n");
		
		printf("Digite o nome do arquivo que deseja ler ou SAIR para terminar o programa: ");
		scanf("%s", &arquivo);
	}
	
	printf("\nSaindo...\n");
	return 0;
}

