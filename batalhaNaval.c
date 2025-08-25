#include <stdio.h>

#define TAM 10      // Tamanho do tabuleiro (10x10)
#define NAVIO 3     // Valor que representa a parte de um navio
#define TAMANHO 3   // Tamanho fixo dos navios (3 posições)

// Função para inicializar o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para verificar se um navio cabe dentro do tabuleiro
int validarPosicao(int linha, int coluna, int orientacao, int tabuleiro[TAM][TAM]) {
    // orientacao = 0 → horizontal, 1 → vertical

    if (orientacao == 0) { // horizontal
        if (coluna + TAMANHO > TAM) return 0; // não cabe
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[linha][coluna + j] != 0) return 0; // já ocupado
        }
    } else { // vertical
        if (linha + TAMANHO > TAM) return 0; // não cabe
        for (int i = 0; i < TAMANHO; i++) {
            if (tabuleiro[linha + i][coluna] != 0) return 0; // já ocupado
        }
    }
    return 1; // posição válida
}

// Função para posicionar o navio
void posicionarNavio(int linha, int coluna, int orientacao, int tabuleiro[TAM][TAM]) {
    if (orientacao == 0) { // horizontal
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[linha][coluna + j] = NAVIO;
        }
    } else { // vertical
        for (int i = 0; i < TAMANHO; i++) {
            tabuleiro[linha + i][coluna] = NAVIO;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\nTabuleiro Batalha Naval:\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];

    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // Definindo manualmente as coordenadas iniciais dos navios
    int linha1 = 2, coluna1 = 1, orientacao1 = 0; // navio 1 horizontal
    int linha2 = 5, coluna2 = 4, orientacao2 = 1; // navio 2 vertical

    // Valida e posiciona o primeiro navio
    if (validarPosicao(linha1, coluna1, orientacao1, tabuleiro)) {
        posicionarNavio(linha1, coluna1, orientacao1, tabuleiro);
    } else {
        printf("Erro: nao foi possivel posicionar o navio 1!\n");
    }

    // Valida e posiciona o segundo navio
    if (validarPosicao(linha2, coluna2, orientacao2, tabuleiro)) {
        posicionarNavio(linha2, coluna2, orientacao2, tabuleiro);
    } else {
        printf("Erro: nao foi possivel posicionar o navio 2!\n");
    }

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}