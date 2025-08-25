#include <stdio.h>

#define TAM 10      // Tamanho do tabuleiro (10x10)
#define NAVIO 3     // Valor que representa uma parte do navio
#define TAMANHO 3   // Tamanho fixo dos navios (3 casas)

// Função para inicializar o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para validar se o navio pode ser colocado sem sair do tabuleiro ou sobrepor outro
int validarPosicao(int linha, int coluna, int orientacao, int tabuleiro[TAM][TAM]) {
    // orientacao: 0=horizontal, 1=vertical, 2=diagonal ↘, 3=diagonal ↙

    if (orientacao == 0) { // Horizontal →
        if (coluna + TAMANHO > TAM) return 0; // não cabe
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[linha][coluna + j] != 0) return 0; // sobreposição
        }
    } 
    else if (orientacao == 1) { // Vertical ↓
        if (linha + TAMANHO > TAM) return 0;
        for (int i = 0; i < TAMANHO; i++) {
            if (tabuleiro[linha + i][coluna] != 0) return 0;
        }
    } 
    else if (orientacao == 2) { // Diagonal ↘ (linha+ e coluna+)
        if (linha + TAMANHO > TAM || coluna + TAMANHO > TAM) return 0;
        for (int k = 0; k < TAMANHO; k++) {
            if (tabuleiro[linha + k][coluna + k] != 0) return 0;
        }
    } 
    else if (orientacao == 3) { // Diagonal ↙ (linha+ e coluna-)
        if (linha + TAMANHO > TAM || coluna - (TAMANHO - 1) < 0) return 0;
        for (int k = 0; k < TAMANHO; k++) {
            if (tabuleiro[linha + k][coluna - k] != 0) return 0;
        }
    }
    return 1; // posição válida
}

// Função para posicionar o navio no tabuleiro
void posicionarNavio(int linha, int coluna, int orientacao, int tabuleiro[TAM][TAM]) {
    if (orientacao == 0) { // Horizontal
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[linha][coluna + j] = NAVIO;
        }
    } 
    else if (orientacao == 1) { // Vertical
        for (int i = 0; i < TAMANHO; i++) {
            tabuleiro[linha + i][coluna] = NAVIO;
        }
    } 
    else if (orientacao == 2) { // Diagonal ↘
        for (int k = 0; k < TAMANHO; k++) {
            tabuleiro[linha + k][coluna + k] = NAVIO;
        }
    } 
    else if (orientacao == 3) { // Diagonal ↙
        for (int k = 0; k < TAMANHO; k++) {
            tabuleiro[linha + k][coluna - k] = NAVIO;
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

    // Definição manual das posições dos 4 navios
    int navios[4][3] = {
        {2, 1, 0}, // linha=2, coluna=1, horizontal →
        {5, 4, 1}, // linha=5, coluna=4, vertical ↓
        {0, 0, 2}, // linha=0, coluna=0, diagonal ↘
        {0, 9, 3}  // linha=0, coluna=9, diagonal ↙
    };

    // Posiciona os navios no tabuleiro
    for (int n = 0; n < 4; n++) {
        int linha = navios[n][0];
        int coluna = navios[n][1];
        int orientacao = navios[n][2];

        if (validarPosicao(linha, coluna, orientacao, tabuleiro)) {
            posicionarNavio(linha, coluna, orientacao, tabuleiro);
        } else {
            printf("Erro: nao foi possivel posicionar o navio %d!\n", n + 1);
        }
    }

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}