#include <stdio.h>

int main() {

    char nome[50];
    int opcao;

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
        printf("\nO jogo vai comecar!\n");
    }
    else if (opcao == 2) {
        printf("\nA sair do jogo...\n");
    }
    else {
        printf("\nOpcao invalida.\n");
    }

    return 0;
}