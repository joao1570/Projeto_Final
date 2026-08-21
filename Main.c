#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void preencherTabuleiros(char tabuleiroBarcos[6][6], char tabuleiroJogador[6][6]) {

    int linha, coluna;

    for (linha = 0; linha < 6; linha++) {
        for (coluna = 0; coluna < 6; coluna++) {
            tabuleiroBarcos[linha][coluna] = '~';
            tabuleiroJogador[linha][coluna] = '~';
        }
    }
}

void colocarBarcos(char tabuleiroBarcos[6][6]) {

    int linha, coluna;
    int barcosColocados = 0;

    while (barcosColocados < 3) {

        linha = rand() % 6;
        coluna = rand() % 6;

        if (tabuleiroBarcos[linha][coluna] != 'B') {

            tabuleiroBarcos[linha][coluna] = 'B';
            barcosColocados++;
        }
    }
}

void mostrarTabuleiro(char tabuleiroJogador[6][6]) {

    int linha, coluna;

    printf("\nTabuleiro:\n\n");
    printf("  1 2 3 4 5 6\n");

    for (linha = 0; linha < 6; linha++) {

        printf("%d ", linha + 1);

        for (coluna = 0; coluna < 6; coluna++) {
            printf("%c ", tabuleiroJogador[linha][coluna]);
        }

        printf("\n");
    }
}

int main() {

    srand(time(NULL));

    char nome[50];
    int opcao;
    char tabuleiroBarcos[6][6];
    char tabuleiroJogador[6][6];
    int linha, coluna;
    int barcosDestruidos = 0;
    int tentativas = 0;

    printf("=================================\n");
    printf("        BATALHA NAVAL\n");
    printf("=================================\n\n");

    printf("Introduz o teu nome: ");
    scanf("%49s", nome);

    printf("\nBem-vindo, %s!\n", nome);

    printf("\n1 - Jogar\n");
    printf("2 - Sair\n");

    printf("\nEscolhe uma opcao: ");
    scanf("%d", &opcao);

    if (opcao == 1) {

        preencherTabuleiros(tabuleiroBarcos, tabuleiroJogador);

        colocarBarcos(tabuleiroBarcos);

        while (barcosDestruidos < 3) {

            mostrarTabuleiro(tabuleiroJogador);

            printf("\nBarcos destruidos: %d/3\n", barcosDestruidos);

            printf("\nEscolhe onde queres disparar.\n");

            printf("Linha (1-6): ");
            scanf("%d", &linha);

            printf("Coluna (1-6): ");
            scanf("%d", &coluna);

            if (linha < 1 || linha > 6 || coluna < 1 || coluna > 6) {

                printf("\nPosicao invalida. Escolhe valores entre 1 e 6.\n");
                continue;
            }

            linha--;
            coluna--;

            if (tabuleiroJogador[linha][coluna] == 'X' ||
                tabuleiroJogador[linha][coluna] == 'O') {

                printf("\nJa disparaste nessa posicao.\n");
                continue;
            }

            tentativas++;

            if (tabuleiroBarcos[linha][coluna] == 'B') {

                printf("\nAcertaste num barco!\n");

                tabuleiroJogador[linha][coluna] = 'X';
                tabuleiroBarcos[linha][coluna] = '~';

                barcosDestruidos++;
            }
            else {

                printf("\nFalhaste!\n");

                tabuleiroJogador[linha][coluna] = 'O';
            }
        }

        printf("\n=================================\n");
        printf("        GANHASTE, %s!\n", nome);
        printf("=================================\n");

        printf("\nDestruiste todos os barcos!\n");
        printf("Numero de tentativas: %d\n", tentativas);
    }
    else if (opcao == 2) {

        printf("\nA sair do jogo...\n");
    }
    else {

        printf("\nOpcao invalida.\n");
    }

    return 0;
}