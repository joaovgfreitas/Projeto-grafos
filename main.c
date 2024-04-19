#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *file;
	file = fopen("teste.txt", "r");
	
	if(file == NULL){
		printf("Nao foi possivel abrir arquivo.");
		getchar();
		exit(0);
	}
	
	char frase[100];
	
	while(fgets(frase, 100, file) != NULL){
		printf("%s", frase);
	}
	
	fclose(file);
	printf("\n");
	system("pause");
	return 0;
}

//TESTE
