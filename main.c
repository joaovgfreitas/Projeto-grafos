#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

int main(int argc, char *argv[]) {
	FILE *file;
	int  i = 0;
	char matriz[MAX][MAX], arquivo[30], frase[100];
	
	printf("Digite o nome do arquivo que deseja ler ou SAIR para terminar o programa: ");
	scanf("%s", &arquivo);
	
	while(strcmp(arquivo, "SAIR") != 0){
		
		snprintf(arquivo, sizeof(arquivo), "%s.txt",arquivo);
		file = fopen(arquivo, "r");
			
		if(file == NULL){
			printf("Nao foi possivel abrir arquivo.");
		}
	
		while(fgets(frase, 100, file) != NULL){
			strcpy(matriz[i], frase);	
			printf("%s", matriz[i]);
			i++;
		}
	
		fclose(file);
		printf("\n\n");
		
		printf("Digite o nome do arquivo que deseja ler ou SAIR para terminar o programa: ");
		scanf("%s", &arquivo);
	}
	
	printf("\nSaindo...\n");
	return 0;
}

//TESTE
