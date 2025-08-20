#include <stdio.h>
#include <stdlib.h> // Para a função abs()

// Definições de constantes para o tabuleiro e habilidades
#define TABULEIRO_SIZE 10
#define HABILIDADE_SIZE 5
#define AGUA 0
#define NAVIO 3
#define HABILIDADE_MARC 5

// --- Protótipos das Funções ---
void inicializarTabuleiro(int tabuleiro[TABULEIRO_SIZE][TABULEIRO_SIZE]);
void exibirTabuleiro(int tabuleiro[TABULEIRO_SIZE][TABULEIRO_SIZE]);
void criarHabilidadeCone(int habilidade[HABILIDADE_SIZE][HABILIDADE_SIZE]);
void criarHabilidadeCruz(int habilidade[HABILIDADE_SIZE][HABILIDADE_SIZE]);
void criarHabilidadeOctaedro(int habilidade[HABILIDADE_SIZE][HABILIDADE_SIZE]);
void aplicarHabilidadeNoTabuleiro(int tabuleiro[TABULEIRO_SIZE][TABULEIRO_SIZE], int habilidade[HABILIDADE_SIZE][HABILIDADE_SIZE], int linhaOrigem, int colunaOrigem);

// --- Função Principal ---
int main() {
    int tabuleiro[TABULEIRO_SIZE][TABULEIRO_SIZE];
    int habilidadeCone[HABILIDADE_SIZE][HABILIDADE_SIZE];
    int habilidadeCruz[HABILIDADE_SIZE][HABILIDADE_SIZE];
    int habilidadeOctaedro[HABILIDADE_SIZE][HABILIDADE_SIZE];

    // Ponto de origem fixo para a aplicação das habilidades
    int linhaOrigem = 4;
    int colunaOrigem = 4;

    // --- Demonstrando a Habilidade Cone ---
    printf("--- Habilidade Cone ---\n");
    inicializarTabuleiro(tabuleiro);
    // Adiciona alguns navios para visualização
    tabuleiro[3][4] = NAVIO;
    tabuleiro[5][4] = NAVIO;
    tabuleiro[6][3] = NAVIO;
    tabuleiro[6][4] = NAVIO;
    tabuleiro[6][5] = NAVIO;

    criarHabilidadeCone(habilidadeCone);
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidadeCone, linhaOrigem, colunaOrigem);
    exibirTabuleiro(tabuleiro);
    printf("\n");

    // --- Demonstrando a Habilidade Cruz ---
    printf("--- Habilidade Cruz ---\n");
    inicializarTabuleiro(tabuleiro);
    // Adiciona navios para o teste da Cruz
    tabuleiro[4][2] = NAVIO;
    tabuleiro[4][3] = NAVIO;
    tabuleiro[4][5] = NAVIO;
    tabuleiro[4][6] = NAVIO;
    tabuleiro[2][4] = NAVIO;
    tabuleiro[3][4] = NAVIO;
    tabuleiro[5][4] = NAVIO;
    tabuleiro[6][4] = NAVIO;

    criarHabilidadeCruz(habilidadeCruz);
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidadeCruz, linhaOrigem, colunaOrigem);
    exibirTabuleiro(tabuleiro);
    printf("\n");

    // --- Demonstrando a Habilidade Octaedro ---
    printf("--- Habilidade Octaedro (Losango) ---\n");
    inicializarTabuleiro(tabuleiro);
    // Adiciona navios para o teste do Octaedro
    tabuleiro[4][4] = NAVIO;
    tabuleiro[3][4] = NAVIO;
    tabuleiro[5][4] = NAVIO;
    tabuleiro[4][3] = NAVIO;
    tabuleiro[4][5] = NAVIO;
    tabuleiro[2][4] = NAVIO;
    tabuleiro[4][2] = NAVIO;
    tabuleiro[4][6] = NAVIO;
    tabuleiro[6][4] = NAVIO;

    criarHabilidadeOctaedro(habilidadeOctaedro);
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidadeOctaedro, linhaOrigem, colunaOrigem);
    exibirTabuleiro(tabuleiro);
    printf("\n");

    return 0;
}

// --- Implementação das Funções ---

/**
 * @brief Inicializa o tabuleiro com o valor de Água.
 * * @param tabuleiro A matriz do tabuleiro 10x10.
 */
void inicializarTabuleiro(int tabuleiro[TABULEIRO_SIZE][TABULEIRO_SIZE]) {
    for (int i = 0; i < TABULEIRO_SIZE; i++) {
        for (int j = 0; j < TABULEIRO_SIZE; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

/**
 * @brief Exibe o tabuleiro no console, usando caracteres diferentes para cada elemento.
 * * @param tabuleiro A matriz do tabuleiro 10x10.
 */
void exibirTabuleiro(int tabuleiro[TABULEIRO_SIZE][TABULEIRO_SIZE]) {
    printf("  0 1 2 3 4 5 6 7 8 9\n"); // Imprime os números das colunas
    for (int i = 0; i < TABULEIRO_SIZE; i++) {
        printf("%d ", i); // Imprime o número da linha
        for (int j = 0; j < TABULEIRO_SIZE; j++) {
            // Usa condicionais para determinar o caractere a ser impresso
            if (tabuleiro[i][j] == AGUA) {
                printf("~ "); // Água
            } else if (tabuleiro[i][j] == NAVIO) {
                printf("N "); // Navio
            } else if (tabuleiro[i][j] == HABILIDADE_MARC) {
                printf("X "); // Área de efeito da habilidade
            } else {
                printf("? "); // Caractere para valores desconhecidos
            }
        }
        printf("\n");
    }
}

/**
 * @brief Cria uma matriz 5x5 representando a área de efeito de um Cone.
 * A área em forma de cone se expande para baixo a partir do topo.
 * * @param habilidade A matriz 5x5 que será preenchida.
 */
void criarHabilidadeCone(int habilidade[HABILIDADE_SIZE][HABILIDADE_SIZE]) {
    int centro = HABILIDADE_SIZE / 2;
    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        for (int j = 0; j < HABILIDADE_SIZE; j++) {
            // O cone se expande para baixo. A lógica de preenchimento
            // é baseada na distância da coluna em relação ao centro da linha,
            // que deve ser menor ou igual à linha atual.
            if (abs(j - centro) <= i) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

/**
 * @brief Cria uma matriz 5x5 representando a área de efeito de uma Cruz.
 * A área afeta a linha e a coluna que passam pelo centro da matriz.
 * * @param habilidade A matriz 5x5 que será preenchida.
 */
void criarHabilidadeCruz(int habilidade[HABILIDADE_SIZE][HABILIDADE_SIZE]) {
    int centro = HABILIDADE_SIZE / 2;
    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        for (int j = 0; j < HABILIDADE_SIZE; j++) {
            // Se a posição estiver na mesma linha ou coluna do centro, ela é afetada.
            if (i == centro || j == centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

/**
 * @brief Cria uma matriz 5x5 representando a área de efeito de um Octaedro (Losango).
 * A área de efeito se assemelha a um losango com o centro como origem.
 * * @param habilidade A matriz 5x5 que será preenchida.
 */
void criarHabilidadeOctaedro(int habilidade[HABILIDADE_SIZE][HABILIDADE_SIZE]) {
    int centro = HABILIDADE_SIZE / 2;
    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        for (int j = 0; j < HABILIDADE_SIZE; j++) {
            // A lógica é baseada na "distância de Manhattan" do centro.
            // A soma da distância da linha e da coluna ao centro deve ser menor ou igual ao raio.
            if (abs(i - centro) + abs(j - centro) <= centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

/**
 * @brief Sobrepõe a matriz de habilidade ao tabuleiro principal.
 * A área de efeito é centrada no ponto de origem definido.
 * * @param tabuleiro A matriz do tabuleiro 10x10.
 * @param habilidade A matriz de habilidade 5x5.
 * @param linhaOrigem A linha do tabuleiro onde a habilidade será centrada.
 * @param colunaOrigem A coluna do tabuleiro onde a habilidade será centrada.
 */
void aplicarHabilidadeNoTabuleiro(int tabuleiro[TABULEIRO_SIZE][TABULEIRO_SIZE], int habilidade[HABILIDADE_SIZE][HABILIDADE_SIZE], int linhaOrigem, int colunaOrigem) {
    int metadeHabilidade = HABILIDADE_SIZE / 2;

    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        for (int j = 0; j < HABILIDADE_SIZE; j++) {
            // Se a posição da matriz de habilidade for 1 (afetada)
            if (habilidade[i][j] == 1) {
                // Mapeia as coordenadas da matriz de habilidade para o tabuleiro principal
                int tabuleiro_linha = linhaOrigem + (i - metadeHabilidade);
                int tabuleiro_coluna = colunaOrigem + (j - metadeHabilidade);

                // Verifica se as coordenadas calculadas estão dentro dos limites do tabuleiro
                if (tabuleiro_linha >= 0 && tabuleiro_linha < TABULEIRO_SIZE &&
                    tabuleiro_coluna >= 0 && tabuleiro_coluna < TABULEIRO_SIZE) {
                    
                    // Marca a posição no tabuleiro com o valor de habilidade
                    tabuleiro[tabuleiro_linha][tabuleiro_coluna] = HABILIDADE_MARC;
                }
            }
        }
    }
}
