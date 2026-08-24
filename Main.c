#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Preenche os dois tabuleiros com agua (~)
void preencherTabuleiros(char tabuleiroBarcos[6][6], char tabuleiroJogador[6][6]) {

    int linha, coluna;

    // Percorre todas as linhas e colunas dos tabuleiros
    for (linha = 0; linha < 6; linha++) {
        for (coluna = 0; coluna < 6; coluna++) {
            tabuleiroBarcos[linha][coluna] = '~';
            tabuleiroJogador[linha][coluna] = '~';
        }
    }
}

// Coloca 3 barcos em posicoes aleatorias
void colocarBarcos(char tabuleiroBarcos[6][6]) {

    int linha, coluna;
    int barcosColocados = 0;

    // Continua ate colocar os 3 barcos
    while (barcosColocados < 3) {

        // Gera uma linha e uma coluna aleatorias entre 0 e 5
        linha = rand() % 6;
        coluna = rand() % 6;

        // Verifica se ainda nao existe um barco nessa posicao
        if (tabuleiroBarcos[linha][coluna] != 'B') {

            tabuleiroBarcos[linha][coluna] = 'B';
            barcosColocados++;
        }
    }
}

// Mostra no ecra o tabuleiro que o jogador pode ver
void mostrarTabuleiro(char tabuleiroJogador[6][6]) {

    int linha, coluna;

    printf("\nTabuleiro:\n\n");
    printf("  1 2 3 4 5 6\n");

    // Percorre o tabuleiro e mostra cada posicao
    for (linha = 0; linha < 6; linha++) {

        printf("%d ", linha + 1);

        for (coluna = 0; coluna < 6; coluna++) {
            printf("%c ", tabuleiroJogador[linha][coluna]);
        }

        printf("\n");
    }
}

// Pede uma opcao ao jogador e valida a resposta
int escolherOpcao() {

    int opcao;

    printf("\n1 - Jogar\n");
    printf("2 - Sair\n");

    printf("\nEscolhe uma opcao: ");
    scanf("%d", &opcao);

    // Se a opcao for invalida, a funcao chama-se novamente
    // Isto e um exemplo de recursao
    if (opcao != 1 && opcao != 2) {

        printf("\nOpcao invalida. Tenta novamente.\n");

        return escolherOpcao();
    }

    return opcao;
}

// Controla uma partida completa
void jogarPartida(char nome[50]) {

    char tabuleiroBarcos[6][6];
    char tabuleiroJogador[6][6];

    int linha, coluna;
    int barcosDestruidos = 0;
    int tentativas = 0;

    // Prepara os tabuleiros para uma nova partida
    preencherTabuleiros(tabuleiroBarcos, tabuleiroJogador);

    // Coloca os barcos no tabuleiro escondido
    colocarBarcos(tabuleiroBarcos);

    // O jogo continua enquanto ainda existirem barcos
    while (barcosDestruidos < 3) {

        mostrarTabuleiro(tabuleiroJogador);

        printf("\nBarcos destruidos: %d/3\n", barcosDestruidos);

        printf("\nEscolhe onde queres disparar.\n");

        printf("Linha (1-6): ");
        scanf("%d", &linha);

        printf("Coluna (1-6): ");
        scanf("%d", &coluna);

        // Verifica se a posicao escolhida existe no tabuleiro
        if (linha < 1 || linha > 6 ||
            coluna < 1 || coluna > 6) {

            printf("\nPosicao invalida. Escolhe valores entre 1 e 6.\n");
            continue;
        }

        // Converte os valores de 1-6 para indices de 0-5
        linha--;
        coluna--;

        // Verifica se o jogador ja disparou nessa posicao
        if (tabuleiroJogador[linha][coluna] == 'X' ||
            tabuleiroJogador[linha][coluna] == 'O') {

            printf("\nJa disparaste nessa posicao.\n");
            continue;
        }

        // Conta apenas os disparos validos
        tentativas++;

        // Verifica se existe um barco na posicao escolhida
        if (tabuleiroBarcos[linha][coluna] == 'B') {

            printf("\nAcertaste num barco!\n");

            // X representa um barco atingido
            tabuleiroJogador[linha][coluna] = 'X';

            // Retira o barco do tabuleiro escondido
            tabuleiroBarcos[linha][coluna] = '~';

            barcosDestruidos++;
        }
        else {

            printf("\nFalhaste!\n");

            // O representa um disparo que falhou
            tabuleiroJogador[linha][coluna] = 'O';
        }
    }

    // Mostra o tabuleiro final depois de destruir os 3 barcos
    mostrarTabuleiro(tabuleiroJogador);

    printf("\n=================================\n");
    printf("        GANHASTE, %s!\n", nome);
    printf("=================================\n");

    printf("\nDestruiste todos os barcos!\n");
    printf("Numero de tentativas: %d\n", tentativas);

    printf("\nPodes jogar novamente pelo menu.\n");
}

int main() {

    // Inicializa os numeros aleatorios
    srand(time(NULL));

    char nome[50];
    int opcao;

    printf("=================================\n");
    printf("        BATALHA NAVAL\n");
    printf("=================================\n\n");

    // Le o nome do jogador
    // %49s limita a leitura para nao ultrapassar o tamanho da string
    printf("Introduz o teu nome: ");
    scanf("%49s", nome);

    printf("\nBem-vindo, %s!\n", nome);

    // Mantem o programa aberto ate o jogador escolher sair
    do {

        opcao = escolherOpcao();

        // Se escolher 1, inicia uma nova partida
        if (opcao == 1) {
            jogarPartida(nome);
        }

    } while (opcao != 2);

    printf("\nA sair do jogo...\n");

    return 0;
}