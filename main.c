#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *file;
	file = fopen("teste.txt", "r");
	
	if(file == NULL){
		printf("Erro, arquivo nao pode ser aberto \n");
		system("pause");
		return 0;
	}
	
	int x, y, z;
	
	fscanf(file,"%i %i %i", &x, &y, &z);
	
	printf("%i %i %i", x, y, z);
	
	fclose(file);
	
	return 0;
}
