#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 100

int numVertices;

bool existeCaminho(int grafo[numVertices][numVertices], int origem, int destino) {
    bool visitados[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visitados[i] = false; // Inicializa todos os v�rtices como n�o visitados
    }

    // Marca o v�rtice de origem como visitado
    visitados[origem] = true;

    // Cria uma pilha para fazer a busca em profundidade
    int pilha[numVertices];
    int topo = -1; // Inicializa o topo da pilha

    pilha[++topo] = origem; // Adiciona a origem � pilha

    while (topo != -1) { // Enquanto a pilha n�o estiver vazia
        int atual = pilha[topo--]; // Remove o v�rtice do topo da pilha

        // Verifica se o v�rtice atual � o destino
        if (atual == destino) {
            return true; // Se sim, retorna true (existe caminho)
        }

        // Percorre todos os v�rtices adjacentes ao v�rtice atual
        for (int i = 0; i < numVertices; i++) {
            // Verifica se o v�rtice ainda n�o foi visitado e se h� uma aresta entre o v�rtice atual e o v�rtice i
            if (!visitados[i] && grafo[atual][i]) {
                visitados[i] = true; // Marca o v�rtice como visitado
                pilha[++topo] = i; // Adiciona o v�rtice � pilha
            }
        }
    }

    return false; // Se n�o encontrou um caminho, retorna false
}

int main(int argc, char *argv[]) {
    FILE *file;
    bool temCaminho;

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

        numVertices = 0; // Reinicia o contador de v�rtices
        while (fgets(frase, MAX, file) != NULL) { // Percorre linha por linha do txt
            numVertices++; // Contagem do n�mero de v�rtices
        }

        fclose(file); // Fecha o arquivo

        // Reabre o arquivo para ler a matriz do in�cio
        file = fopen(arquivo, "r");
        if (file == NULL) {
            printf("Nao foi possivel abrir arquivo.");
            return 1;
        }

        int grafo[numVertices][numVertices], backup[numVertices][numVertices]; // Declara��o da MA
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                fscanf(file, "%i", &grafo[i][j]); // L� caracter por caracter e escreve na matriz de inteiros
                backup[i][j] = grafo[i][j]; // Inicializa a matriz backup
                printf("%i ", grafo[i][j]); // Exibe a MA
            }
            printf("\n");
        }
        fclose(file); // Fecha o arquivo

        int articulacao[numVertices];
        int countDesconectam = 0;

        for (int verticeRemover = 0; verticeRemover < numVertices; verticeRemover++) {
            // Remove o v�rtice verticeRemover da matriz de adjac�ncia
            for (int i = 0; i < numVertices; i++) {
                grafo[verticeRemover][i] = 0;
                grafo[i][verticeRemover] = 0;
            }

            // Testa se o grafo ainda � conexo
            temCaminho = true;
            for (int verticeDestino = 0; verticeDestino < numVertices; verticeDestino++) {
                if (verticeDestino != verticeRemover && !existeCaminho(grafo, 0, verticeDestino)) {
                    temCaminho = false;
                    break;
                }
            }

            if (!temCaminho) {
                articulacao[countDesconectam++] = verticeRemover;
            }

            // Restaura a matriz de adjac�ncia original
            for (int i = 0; i < numVertices; i++) {
                for (int j = 0; j < numVertices; j++) {
                    grafo[i][j] = backup[i][j];
                }
            }
        }

        // Imprime os v�rtices que desconectam o grafo
        if (countDesconectam > 0) {
            printf("\nAs Articulacoes sao os vertices: ");
            for (int i = 0; i < countDesconectam; i++) {
                printf("%d ", articulacao[i] + 1);
            }
        } else {
            printf("O grafo nao tem articulacao\n");
        }

        printf("\nDigite o nome do arquivo que deseja ler ou SAIR para terminar o programa: ");
        scanf("%s", arquivo);
    }

    printf("\nSaindo...\n");
    return 0;
}

