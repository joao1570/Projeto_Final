#include <stdlib.h>
#include <stdio.h>
#include <ncurses/ncurses.h>

#include "game.h"

// Preenche os dois tabuleiros com agua (~)
void preencherTabuleiros(
    char tabuleiroBarcos[TAMANHO][TAMANHO],
    char tabuleiroJogador[TAMANHO][TAMANHO]
) {

    int linha, coluna;

    for (linha = 0; linha < TAMANHO; linha++) {

        for (coluna = 0; coluna < TAMANHO; coluna++) {

            tabuleiroBarcos[linha][coluna] = '~';
            tabuleiroJogador[linha][coluna] = '~';
        }
    }
}


// Coloca os barcos em posicoes aleatorias
void colocarBarcos(
    char tabuleiroBarcos[TAMANHO][TAMANHO]
) {

    int linha, coluna;
    int barcosColocados = 0;

    while (barcosColocados < NUM_BARCOS) {

        linha = rand() % TAMANHO;
        coluna = rand() % TAMANHO;

        // Verifica se ainda nao existe um barco nessa posicao
        if (tabuleiroBarcos[linha][coluna] != 'B') {

            tabuleiroBarcos[linha][coluna] = 'B';

            barcosColocados++;
        }
    }
}


// Mostra o tabuleiro utilizando ncurses
void mostrarTabuleiro(
    char tabuleiroJogador[TAMANHO][TAMANHO],
    int cursorLinha,
    int cursorColuna
) {

    int linha, coluna;

    printw("       1   2   3   4   5   6\n\n");

    for (linha = 0; linha < TAMANHO; linha++) {

        printw(" %d     ", linha + 1);

        for (coluna = 0; coluna < TAMANHO; coluna++) {

            char posicao = tabuleiroJogador[linha][coluna];

            // Verifica se esta e a posicao atual do cursor
            if (linha == cursorLinha &&
                coluna == cursorColuna) {

                attron(COLOR_PAIR(4));

                printw(" %c ", posicao);

                attroff(COLOR_PAIR(4));
            }

            // X significa barco atingido
            else if (posicao == 'X') {

                attron(COLOR_PAIR(2));

                printw(" X ");

                attroff(COLOR_PAIR(2));
            }

            // O significa tiro falhado
            else if (posicao == 'O') {

                attron(COLOR_PAIR(3));

                printw(" O ");

                attroff(COLOR_PAIR(3));
            }

            // ~ representa agua
            else {

                attron(COLOR_PAIR(1));

                printw(" ~ ");

                attroff(COLOR_PAIR(1));
            }

            printw(" ");
        }

        printw("\n\n");
    }
}


// Pede uma opcao e valida a resposta
int escolherOpcao() {

    int tecla;

    clear();

    printw("=================================\n");
    printw("        BATALHA NAVAL\n");
    printw("=================================\n\n");

    printw("1 - Jogar\n");
    printw("2 - Sair\n\n");

    printw("Escolhe uma opcao: ");

    refresh();

    tecla = getch();

    if (tecla == '1') {
        return 1;
    }

    if (tecla == '2') {
        return 2;
    }

    clear();

    printw("Opcao invalida.\n");
    printw("Prime qualquer tecla para tentar novamente.");

    getch();

    // A funcao chama-se a si propria
    // Isto e um exemplo de recursao
    return escolherOpcao();
}


// Controla uma partida completa
void jogarPartida(char nome[50]) {

    char tabuleiroBarcos[TAMANHO][TAMANHO];
    char tabuleiroJogador[TAMANHO][TAMANHO];

    int cursorLinha = 0;
    int cursorColuna = 0;

    int barcosDestruidos = 0;
    int tentativas = 0;

    int tecla;

    char mensagem[100] = "Escolhe uma posicao para disparar.";

    // Prepara os tabuleiros
    preencherTabuleiros(
        tabuleiroBarcos,
        tabuleiroJogador
    );

    // Coloca os barcos aleatoriamente
    colocarBarcos(tabuleiroBarcos);

    // Continua enquanto existirem barcos
    while (barcosDestruidos < NUM_BARCOS) {

        clear();

        printw("=================================\n");
        printw("        BATALHA NAVAL\n");
        printw("=================================\n\n");

        printw("Jogador: %s\n", nome);

        printw(
            "Barcos destruidos: %d/%d\n",
            barcosDestruidos,
            NUM_BARCOS
        );

        printw(
            "Tentativas: %d\n\n",
            tentativas
        );

        mostrarTabuleiro(
            tabuleiroJogador,
            cursorLinha,
            cursorColuna
        );

        printw("\n%s\n\n", mensagem);

        printw("SETAS  - mover cursor\n");
        printw("ENTER  - disparar\n");

        refresh();

        tecla = getch();

        // Move o cursor para cima
        if (tecla == KEY_UP) {

            if (cursorLinha > 0) {
                cursorLinha--;
            }
        }

        // Move o cursor para baixo
        else if (tecla == KEY_DOWN) {

            if (cursorLinha < TAMANHO - 1) {
                cursorLinha++;
            }
        }

        // Move o cursor para a esquerda
        else if (tecla == KEY_LEFT) {

            if (cursorColuna > 0) {
                cursorColuna--;
            }
        }

        // Move o cursor para a direita
        else if (tecla == KEY_RIGHT) {

            if (cursorColuna < TAMANHO - 1) {
                cursorColuna++;
            }
        }

        // ENTER efetua o disparo
        else if (
            tecla == '\n' ||
            tecla == '\r' ||
            tecla == KEY_ENTER
        ) {

            // Verifica se o jogador ja disparou aqui
            if (
                tabuleiroJogador[cursorLinha][cursorColuna] == 'X' ||
                tabuleiroJogador[cursorLinha][cursorColuna] == 'O'
            ) {

                snprintf(
                    mensagem,
                    sizeof(mensagem),
                    "Ja disparaste nessa posicao."
                );
            }

            else {

                // Conta apenas disparos validos
                tentativas++;

                // Verifica se acertou num barco
                if (
                    tabuleiroBarcos[cursorLinha][cursorColuna] == 'B'
                ) {

                    // X representa um barco atingido
                    tabuleiroJogador[cursorLinha][cursorColuna] = 'X';

                    // Retira o barco do tabuleiro escondido
                    tabuleiroBarcos[cursorLinha][cursorColuna] = '~';

                    barcosDestruidos++;

                    snprintf(
                        mensagem,
                        sizeof(mensagem),
                        "Acertaste num barco!"
                    );
                }

                // Falhou o disparo
                else {

                    // O representa um disparo falhado
                    tabuleiroJogador[cursorLinha][cursorColuna] = 'O';

                    snprintf(
                        mensagem,
                        sizeof(mensagem),
                        "Falhaste!"
                    );
                }
            }
        }
    }

    // Ecra final
    clear();

    printw("=================================\n");

    attron(COLOR_PAIR(5));

    printw("        GANHASTE, %s!\n", nome);

    attroff(COLOR_PAIR(5));

    printw("=================================\n\n");

    // Mostra o tabuleiro final sem cursor
    mostrarTabuleiro(
        tabuleiroJogador,
        -1,
        -1
    );

    printw("\nDestruiste todos os barcos!\n");

    printw(
        "Numero de tentativas: %d\n",
        tentativas
    );

    // Mostra uma classificacao de acordo
    // com o numero de tentativas
    if (tentativas <= 6) {

        printw("Classificacao: EXCELENTE!\n");

    }
    else if (tentativas <= 12) {

        printw("Classificacao: MUITO BOM!\n");

    }
    else if (tentativas <= 20) {

        printw("Classificacao: BOM!\n");

    }
    else {

        printw("Classificacao: PODES MELHORAR!\n");

    }

    printw("\nPrime qualquer tecla para voltar ao menu.");

    refresh();

    getch();
}