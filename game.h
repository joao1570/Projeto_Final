#ifndef GAME_H
#define GAME_H

#define TAMANHO 6
#define NUM_BARCOS 3

void preencherTabuleiros(
    char tabuleiroBarcos[TAMANHO][TAMANHO],
    char tabuleiroJogador[TAMANHO][TAMANHO]
);

void colocarBarcos(
    char tabuleiroBarcos[TAMANHO][TAMANHO]
);

void mostrarTabuleiro(
    char tabuleiroJogador[TAMANHO][TAMANHO],
    int cursorLinha,
    int cursorColuna
);

int escolherOpcao();

void jogarPartida(char nome[50]);

#endif