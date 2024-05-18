#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 100

int numVertices;

// Função para verificar se existe um caminho de origem para destino usando busca em profundidade (DFS)
bool existeCaminho(int grafo[numVertices][numVertices], int origem, int destino) { // O(N^2)
    bool visitados[numVertices];
    for (int i = 0; i < numVertices; i++) { // O(N)
        visitados[i] = false; // Inicializa todos os vértices como não visitados
    }

    visitados[origem] = true; // Marca o vértice de origem como visitado

    int pilha[numVertices];
    int topo = -1; // Inicializa o topo da pilha

    pilha[++topo] = origem; // Adiciona a origem à pilha

    while (topo != -1) { // Enquanto a pilha não estiver vazia // O(N)
        int atual = pilha[topo--]; // Remove o vértice do topo da pilha

        if (atual == destino) { // Verifica se o vértice atual é o destino
            return true; // Se sim, retorna true (existe caminho)
        }

        for (int i = 0; i < numVertices; i++) { // O(N)
            // Verifica se o vértice ainda não foi visitado e se há uma aresta entre o vértice atual e o vértice i
            if (!visitados[i] && grafo[atual][i]) {
                visitados[i] = true; // Marca o vértice como visitado
                pilha[++topo] = i; // Adiciona o vértice à pilha
            }
        }
    }

    return false; // Se não encontrou um caminho, retorna false
}

int main(int argc, char *argv[]) {// O(N^4)
    FILE *file;
    bool temCaminho;

    char arquivo[30], frase[MAX];
    printf("Digite o nome do arquivo que deseja ler ou SAIR para terminar o programa: ");
    scanf("%s", arquivo);

    while (strcmp(arquivo, "SAIR") != 0) { // Loop principal para leitura do arquivo e processamento // O(E)
        snprintf(arquivo, sizeof(arquivo), "%s.txt", arquivo); // Adiciona .txt ao final do nome escrito pelo usuário
        file = fopen(arquivo, "r"); // Carrega o arquivo

        if (file == NULL) { // Verifica se o arquivo carregado é válido
            printf("Nao foi possivel abrir arquivo.");
            return 1;
        }

        numVertices = 0; // Reinicia o contador de vértices
        while (fgets(frase, MAX, file) != NULL) { // Conta o número de linhas no arquivo para determinar o número de vértices // O(N)
            numVertices++;
        }

        fclose(file); // Fecha o arquivo

        // Reabre o arquivo para ler a matriz do início
        file = fopen(arquivo, "r");
        if (file == NULL) {
            printf("Nao foi possivel abrir arquivo.");
            return 1;
        }

        int grafo[numVertices][numVertices], backup[numVertices][numVertices]; // Declaração da matriz de adjacência
        for (int i = 0; i < numVertices; i++) { // Lê a matriz de adjacência do arquivo e inicializa a matriz backup // O(N^2)
            for (int j = 0; j < numVertices; j++) {//O(N)
                fscanf(file, "%i", &grafo[i][j]);
                backup[i][j] = grafo[i][j];
            }
        }
        fclose(file); // Fecha o arquivo

        int articulacao[numVertices];
        int countDesconectam = 0;

        // Verifica cada vértice para determinar se é uma articulação
        for (int verticeRemover = 0; verticeRemover < numVertices; verticeRemover++) { // O(N^4)
            // Remove o vértice da matriz de adjacência
            for (int i = 0; i < numVertices; i++) { // O(N)
                grafo[verticeRemover][i] = 0;
                grafo[i][verticeRemover] = 0;
            }

            // Verifica se o grafo ainda é conexo
            temCaminho = true;
            for (int verticeDestino = 0; verticeDestino < numVertices; verticeDestino++) { // O(N^3)
                if (verticeDestino != verticeRemover && !existeCaminho(grafo, verticeRemover == 0 ? 1 : 0, verticeDestino)) {
                    temCaminho = false;
                    break;
                }
            }

            // Se o grafo não é mais conexo, o vértice removido é uma articulação
            if (!temCaminho) {
                articulacao[countDesconectam++] = verticeRemover;
            }

            // Restaura a matriz de adjacência original
            for (int i = 0; i < numVertices; i++) { // O(N^2)
                for (int j = 0; j < numVertices; j++) {// O(N)
                    grafo[i][j] = backup[i][j];
                }
            }
        }

        // Imprime os vértices que são articulações
        if (countDesconectam > 0) {
            printf("Articulacao: ");
            for (int i = 0; i < countDesconectam; i++) {// O(N)
                printf("%d ", articulacao[i] + 1); // Adiciona 1 para corresponder à numeração dos vértices reais
            }
            printf("\n");
        } else {
            printf("O grafo nao tem articulacao\n");
        }

        printf("\nDigite o nome do arquivo que deseja ler ou SAIR para terminar o programa: ");
        scanf("%s", arquivo);
    }

    printf("\nSaindo...\n");
    return 0;
}

