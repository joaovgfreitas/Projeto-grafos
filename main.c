#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 100

int numVertices;

// Fun��o para verificar se existe um caminho de origem para destino usando busca em profundidade (DFS)
bool existeCaminho(int grafo[numVertices][numVertices], int origem, int destino) { // O(N^2)
    bool visitados[numVertices];
    for (int i = 0; i < numVertices; i++) { // O(N)
        visitados[i] = false; // Inicializa todos os v�rtices como n�o visitados
    }

    visitados[origem] = true; // Marca o v�rtice de origem como visitado

    int pilha[numVertices];
    int topo = -1; // Inicializa o topo da pilha

    pilha[++topo] = origem; // Adiciona a origem � pilha

    while (topo != -1) { // Enquanto a pilha n�o estiver vazia // O(N)
        int atual = pilha[topo--]; // Remove o v�rtice do topo da pilha

        if (atual == destino) { // Verifica se o v�rtice atual � o destino
            return true; // Se sim, retorna true (existe caminho)
        }

        for (int i = 0; i < numVertices; i++) { // O(N)
            // Verifica se o v�rtice ainda n�o foi visitado e se h� uma aresta entre o v�rtice atual e o v�rtice i
            if (!visitados[i] && grafo[atual][i]) {
                visitados[i] = true; // Marca o v�rtice como visitado
                pilha[++topo] = i; // Adiciona o v�rtice � pilha
            }
        }
    }

    return false; // Se n�o encontrou um caminho, retorna false
}

int main(int argc, char *argv[]) {// O(N^4)
    FILE *file;
    bool temCaminho;

    char arquivo[30], frase[MAX];
    printf("Digite o nome do arquivo que deseja ler ou SAIR para terminar o programa: ");
    scanf("%s", arquivo);

    while (strcmp(arquivo, "SAIR") != 0) { // Loop principal para leitura do arquivo e processamento // O(E)
        snprintf(arquivo, sizeof(arquivo), "%s.txt", arquivo); // Adiciona .txt ao final do nome escrito pelo usu�rio
        file = fopen(arquivo, "r"); // Carrega o arquivo

        if (file == NULL) { // Verifica se o arquivo carregado � v�lido
            printf("Nao foi possivel abrir arquivo.");
            return 1;
        }

        numVertices = 0; // Reinicia o contador de v�rtices
        while (fgets(frase, MAX, file) != NULL) { // Conta o n�mero de linhas no arquivo para determinar o n�mero de v�rtices // O(N)
            numVertices++;
        }

        fclose(file); // Fecha o arquivo

        // Reabre o arquivo para ler a matriz do in�cio
        file = fopen(arquivo, "r");
        if (file == NULL) {
            printf("Nao foi possivel abrir arquivo.");
            return 1;
        }

        int grafo[numVertices][numVertices], backup[numVertices][numVertices]; // Declara��o da matriz de adjac�ncia
        for (int i = 0; i < numVertices; i++) { // L� a matriz de adjac�ncia do arquivo e inicializa a matriz backup // O(N^2)
            for (int j = 0; j < numVertices; j++) {//O(N)
                fscanf(file, "%i", &grafo[i][j]);
                backup[i][j] = grafo[i][j];
            }
        }
        fclose(file); // Fecha o arquivo

        int articulacao[numVertices];
        int countDesconectam = 0;

        // Verifica cada v�rtice para determinar se � uma articula��o
        for (int verticeRemover = 0; verticeRemover < numVertices; verticeRemover++) { // O(N^4)
            // Remove o v�rtice da matriz de adjac�ncia
            for (int i = 0; i < numVertices; i++) { // O(N)
                grafo[verticeRemover][i] = 0;
                grafo[i][verticeRemover] = 0;
            }

            // Verifica se o grafo ainda � conexo
            temCaminho = true;
            for (int verticeDestino = 0; verticeDestino < numVertices; verticeDestino++) { // O(N^3)
                if (verticeDestino != verticeRemover && !existeCaminho(grafo, verticeRemover == 0 ? 1 : 0, verticeDestino)) {
                    temCaminho = false;
                    break;
                }
            }

            // Se o grafo n�o � mais conexo, o v�rtice removido � uma articula��o
            if (!temCaminho) {
                articulacao[countDesconectam++] = verticeRemover;
            }

            // Restaura a matriz de adjac�ncia original
            for (int i = 0; i < numVertices; i++) { // O(N^2)
                for (int j = 0; j < numVertices; j++) {// O(N)
                    grafo[i][j] = backup[i][j];
                }
            }
        }

        // Imprime os v�rtices que s�o articula��es
        if (countDesconectam > 0) {
            printf("Articulacao: ");
            for (int i = 0; i < countDesconectam; i++) {// O(N)
                printf("%d ", articulacao[i] + 1); // Adiciona 1 para corresponder � numera��o dos v�rtices reais
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

