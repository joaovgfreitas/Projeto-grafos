#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 100
int i = 0, j = 0, numVertices;

int distMinima(int dist[], bool relaxado[]){ //Econtra o vertice mais pr�ximo que ainda n�o foi relaxado
	int min = INT_MAX, min_indice; //inicializa min como 'infinito' para comparar com as distancias em dist[]
	
	for (i = 0; i < numVertices; i++){
		if (relaxado[i] == false && dist[i] <= min){//Checa se o vertice ainda n�o foi relaxado e se a dist�ncia atual � menor ou igual � encontrada
			min = dist[i];//Atualiza a dist�ncia encontrada
			min_indice = i;//Atualiza o indice encontrado
		}
	}
	return min_indice;//Retorna o ind�ce do vertice mais pr�ximo
}

void printSolution(int dist[]) {//Apenas pra teste
   printf("Vertice \t Distancia da Origem\n");
   for (i = 0; i < numVertices; i++)
      printf("%d \t\t %d\n", i+1, dist[i]);
}

void dijkstra(int grafo[numVertices][numVertices], int raiz){//Encontra o menor caminho de um vertice para os outros
    int dist[numVertices], cont, v; //dist[] � o vetor que armazena a dist�ncia da raiz para os outros vertices
    bool relaxado[numVertices]; //Vetor para controlar qual vertice foi relaxado

    for(i = 0; i < numVertices; i++){
    	dist[i] = INT_MAX, relaxado[i] = false;//Inicializa a dist�nica da raiz para todos os outros vertices como "infinito" e relxado como fal
	}
	
    dist[raiz] = 0;//Inicializa a dist�nica da matriz pra ela mesma como 0

    for(cont = 0; cont < numVertices-1; cont++){
    	int u = distMinima(dist, relaxado);//U � pr�ximo vertice a ser relaxado
    	relaxado[u] = true;//Relaxa o vertice

    	for (v = 0; v < numVertices; v++){
    		if (!relaxado[v] && grafo[u][v] && dist[u] != INT_MAX && dist[u]+grafo[u][v] < dist[v]){ //Checa toda a l�gica do algoritmo de dijkstra
         	dist[v] = dist[u] + grafo[u][v];//Soma os valores de duas arestas e atualiza a dist�ncia do vertice atual
			}
	   }
    }
    printSolution(dist);//TESTE
}

int main(int argc, char *argv[]) {
    FILE *file;
    
    char arquivo[30], frase[MAX];
    printf("Digite o nome do arquivo que deseja ler ou SAIR para terminar o programa: ");
    scanf("%s", arquivo);

    while (strcmp(arquivo, "SAIR") != 0) {
        snprintf(arquivo, sizeof(arquivo), "%s.txt", arquivo); // Adiciona .txt ao final do nome escrito pelo usu�rio
        file = fopen(arquivo, "r"); // Carrega o arquivo

        if (file == NULL) { // Checa se o arquivo carregado � v�lido
            printf("Nao foi possivel abrir arquivo.");
            return 1;
        }
		
		numVertices = 0;//Reinicia o contador de vertices
        while (fgets(frase, MAX, file) != NULL) { // Percorre linha por linha do txt
            numVertices++; // Contagem do n�mero de v�rtices
        }

        fclose(file); // Fecha o arquivo

        // Reabre o arquivo para ler a matriz do inic�o
        file = fopen(arquivo, "r");
        if (file == NULL) {
            printf("Nao foi possivel abrir arquivo.");
            return 1;
        }

        int grafo[numVertices][numVertices];//Declara��o da MA
        for (i = 0; i < numVertices; i++) {
            for (j = 0; j < numVertices; j++) {
                fscanf(file, "%i", &grafo[i][j]);//L� caracter por caracter e escreve na matriz de inteiros;
                printf("%i ", grafo[i][j]);//Exibia a MA
            }
            printf("\n");
        }
		fclose(file); // Fecha o arquivo
		
		int vdijkstra;//Contador para rodar dijkstra em todos os vertices
		for (vdijkstra = 0; vdijkstra < numVertices; vdijkstra++){
			dijkstra(grafo, vdijkstra);//Testa se h� caminho entre todos os vertices
		}

        printf("\nDigite o nome do arquivo que deseja ler ou SAIR para terminar o programa: ");
        scanf("%s", arquivo);
    }

    printf("\nSaindo...\n");
    return 0;
}

