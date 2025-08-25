#include <stdio.h>

#define TAM 10       // Tamanho do tabuleiro (10x10)
#define NAVIO 3      // Valor que representa uma parte de navio
#define HABILIDADE 5 // Valor que representa área afetada pela habilidade
#define H 5          // Tamanho das matrizes de habilidade (5x5)

// Função para inicializar o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\nTabuleiro:\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para criar a matriz Cone (5x5)
void criarCone(int cone[H][H]) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < H; j++) {
            if (j >= H/2 - i && j <= H/2 + i) {
                cone[i][j] = 1; // dentro do cone
            } else {
                cone[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz Cruz (5x5)
void criarCruz(int cruz[H][H]) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < H; j++) {
            if (i == H/2 || j == H/2) {
                cruz[i][j] = 1; // linha central e coluna central
            } else {
                cruz[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz Octaedro (5x5 losango)
void criarOctaedro(int oct[H][H]) {
    int centro = H / 2;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < H; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro) {
                oct[i][j] = 1; // dentro do losango
            } else {
                oct[i][j] = 0;
            }
        }
    }
}

// Função para sobrepor a matriz da habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[H][H], int origemLinha, int origemColuna) {
    int centro = H / 2;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < H; j++) {
            if (habilidade[i][j] == 1) {
                int linha = origemLinha + (i - centro);
                int coluna = origemColuna + (j - centro);

                // Verifica se a posição está dentro dos limites do tabuleiro
                if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM) {
                    if (tabuleiro[linha][coluna] == 0) { 
                        tabuleiro[linha][coluna] = HABILIDADE; // só marca se não for navio
                    }
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // Posiciona manualmente alguns navios (fixo para teste)
    tabuleiro[2][2] = NAVIO;
    tabuleiro[2][3] = NAVIO;
    tabuleiro[2][4] = NAVIO;

    tabuleiro[6][6] = NAVIO;
    tabuleiro[7][6] = NAVIO;
    tabuleiro[8][6] = NAVIO;

    // Cria as matrizes de habilidades
    int cone[H][H], cruz[H][H], oct[H][H];
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(oct);

    // Aplica as habilidades em pontos de origem
    aplicarHabilidade(tabuleiro, cone, 1, 1);   // cone na posição (1,1)
    aplicarHabilidade(tabuleiro, cruz, 5, 5);  // cruz no centro
    aplicarHabilidade(tabuleiro, oct, 8, 3);   // octaedro perto do canto

    // Exibe o tabuleiro com navios e habilidades
    exibirTabuleiro(tabuleiro);

    return 0;
}