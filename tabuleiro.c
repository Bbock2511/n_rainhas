// l1-t2-Bruno Henrique Bock

#include "terminal.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Parte I: Função para verificar ameaças no tabuleiro de N-Rainhas
int n_rainhas(int n, char tab[]) {
    int count_rainhas = 0;

    // Contagem de rainhas e verificação de ameaças
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (tab[i * n + j] == 'X') {
                count_rainhas++;

                // Checa ameaças na mesma linha e coluna
                for (int k = 0; k < n; k++) {
                    if ((k != j && tab[i * n + k] == 'X') || (k != i && tab[k * n + j] == 'X')) {
                        return 1;
                    }
                }

                // Checa ameaças nas diagonais
                for (int d = 1; d < n; d++) {
                    if ((i + d < n && j + d < n && tab[(i + d) * n + (j + d)] == 'X') ||
                        (i - d >= 0 && j - d >= 0 && tab[(i - d) * n + (j - d)] == 'X') ||
                        (i + d < n && j - d >= 0 && tab[(i + d) * n + (j - d)] == 'X') ||
                        (i - d >= 0 && j + d < n && tab[(i - d) * n + (j + d)] == 'X')) {
                        return 1;
                    }
                }
            }
        }
    }

    if (count_rainhas < n) return 0;
    return 2;
}

// Parte II: Função para desenhar o tabuleiro com destaque
void desenha_tabuleiro(int n, char tab[], int lin, int col) {
    int status = n_rainhas(n, tab);
    t_cor_normal();
    t_limpa();  // Limpa a tela antes de redesenhar o tabuleiro

    // Define a cor da borda com base no status do tabuleiro
    if (status == 1) {
        t_cor_fundo(255, 0, 0);  // Vermelho para ameaça
    } else if (status == 2) {
        t_cor_fundo(0, 255, 0);  // Verde para solução correta
    } else {
        t_cor_fundo(255, 255, 0);  // Amarelo para tabuleiro incompleto
    }

    // Desenha a borda superior e inferior
    for (int i = 0; i <= n + 1; i++) {
        t_lincol(1, i + 1);       // Borda superior
        putchar(' ');
        t_lincol(n + 2, i + 1);   // Borda inferior
        putchar(' ');
    }

    // Desenha a borda lateral esquerda e direita
    for (int i = 0; i <= n + 1; i++) {
        t_lincol(i + 0, 0);       // Borda esquerda
        putchar(' ');
        t_lincol(i + 1, n + 2);   // Borda direita
        putchar(' ');
    }

    // Desenha o tabuleiro
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Define a cor de fundo alternada para o tabuleiro de xadrez
            if ((i + j) % 2 == 0) {
                t_cor_fundo(0, 0, 0);  // Preto
            } else {
                t_cor_fundo(200, 200, 200);  // Cinza claro
            }

            // Define a cor de destaque para a posição do cursor
            if (i == lin - 1 && j == col - 1) {
                t_cor_fundo(0, 0, 255);  // Azul para posição de destaque
            }

            if (tab[i * n + j] == 'X') {
                if ((i + j) % 2 == 0) {
                    t_cor_letra(255, 255, 255);  // Branco para fundo preto
                } else {
                    t_cor_letra(0, 0, 0);  // Preto para fundo branco
                }
            } else {
                t_cor_letra(255, 255, 255);  // Define a cor padrão para outros caracteres
            }

            // Desenha a posição
            t_lincol(i + 2, j + 2);
            putchar(tab[i * n + j]);
        }
    }

    t_cor_normal();  // Restaura a cor normal
    t_atualiza();    // Atualiza o terminal para refletir as mudanças
}

// Parte III: Função para tratar as entradas do teclado
bool trata_teclado(int n, char tab[], int *ref_lin, int *ref_col) {
    if (!t_tem_tecla()) return false;

    char tecla = t_tecla();

    if (tecla == '\e') {
        if (t_tem_tecla() && t_tecla() == '[') {
            switch (t_tecla()) {
                case 'A': if (*ref_lin > 1) (*ref_lin)--; break; // seta para cima
                case 'B': if (*ref_lin < n) (*ref_lin)++; break; // seta para baixo
                case 'C': if (*ref_col < n) (*ref_col)++; break; // seta para a direita
                case 'D': if (*ref_col > 1) (*ref_col)--; break; // seta para a esquerda
            }
            return false;
        }
    }

    switch (tecla) {
        case 'w': if (*ref_lin > 1) (*ref_lin)--; break;
        case 's': if (*ref_lin < n) (*ref_lin)++; break;
        case 'a': if (*ref_col > 1) (*ref_col)--; break;
        case 'd': if (*ref_col < n) (*ref_col)++; break;
        case ' ': case '\n': {
            int index = (*ref_lin - 1) * n + (*ref_col - 1);
            tab[index] = (tab[index] == 'X') ? ' ' : 'X';
            break;
        }
        case 'x': return true;
        default: break;
    }
    return false;
}

// Parte IV: Programa principal
int main() {
    int n, lin = 1, col = 1;
    // double tempo = 0;
    printf("Digite o tamanho do tabuleiro: ");
    scanf("%d", &n);

    char *tab = malloc(n * n * sizeof(char));
    for (int i = 0; i < n * n; i++) tab[i] = ' ';

    t_inicializa();
    clock_t inicio = clock();

    while (true) {
        desenha_tabuleiro(n, tab, lin, col);
        if (trata_teclado(n, tab, &lin, &col)) break;
        if (n_rainhas(n, tab) == 2) { // Tabuleiro completo e válido
            desenha_tabuleiro(n, tab, lin, col); 
            clock_t fim = clock();
            double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            
            t_cor_letra(20, 150, 80); // Cor verde para a mensagem
            t_lincol(n + 4, 1); // Linhas extras abaixo do tabuleiro

            printf("Parabéns! Você completou o tabuleiro em %.2f segundos.\n", tempo*100);
            t_atualiza(); // Atualiza o terminal com a mensagem

            t_cochila(5); // Aguarda 5 segundos antes de encerrar
            break;
        }
    }

    t_finaliza();
    free(tab);
    return 0;
}
