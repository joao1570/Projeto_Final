#include <stdio.h>

int main() {

    char nome[50];
    int opcao;
    char tabuleiro[6][6];
    int linha, coluna;

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

        for (linha = 0; linha < 6; linha++) {
            for (coluna = 0; coluna < 6; coluna++) {
                tabuleiro[linha][coluna] = '~';
            }
        }

        printf("\nTabuleiro:\n\n");

        for (linha = 0; linha < 6; linha++) {
            for (coluna = 0; coluna < 6; coluna++) {
                printf("%c ", tabuleiro[linha][coluna]);
            }
            printf("\n");
        }

    }
    else if (opcao == 2) {
        printf("\nA sair do jogo...\n");
    }
    else {
        printf("\nOpcao invalida.\n");
    }

    return 0;
}