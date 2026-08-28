#include <stdlib.h>
#include <time.h>
#include <ncurses/ncurses.h>

#include "game.h"

int main() {

    char nome[50];
    int opcao;

    // Inicializa os numeros aleatorios
    srand(time(NULL));

    // Inicializa o ncurses
    initscr();

    // Permite usar as setas do teclado
    keypad(stdscr, TRUE);

    // As teclas sao lidas imediatamente
    cbreak();

    // Ativa as cores, caso o terminal suporte
    if (has_colors()) {
        start_color();

        // Cor 1 - agua
        init_pair(1, COLOR_BLUE, COLOR_BLACK);

        // Cor 2 - barco atingido
        init_pair(2, COLOR_RED, COLOR_BLACK);

        // Cor 3 - tiro falhado
        init_pair(3, COLOR_WHITE, COLOR_BLACK);

        // Cor 4 - cursor
        init_pair(4, COLOR_BLACK, COLOR_YELLOW);

        // Cor 5 - mensagens de sucesso
        init_pair(5, COLOR_GREEN, COLOR_BLACK);
    }

    clear();

    printw("=================================\n");
    printw("        BATALHA NAVAL\n");
    printw("=================================\n\n");

    // Permite mostrar aquilo que o jogador escreve
    echo();

    printw("Introduz o teu nome: ");
    getnstr(nome, 49);

    // Volta a esconder as teclas premidas
    noecho();

    printw("\nBem-vindo, %s!\n", nome);
    printw("\nPrime qualquer tecla para continuar.");

    getch();

    // Mantem o jogo aberto ate o jogador escolher sair
    do {

        opcao = escolherOpcao();

        if (opcao == 1) {
            jogarPartida(nome);
        }

    } while (opcao != 2);

    clear();

    printw("A sair do jogo...\n");
    refresh();

    napms(1000);

    // Fecha corretamente o ncurses
    endwin();

    return 0;
}