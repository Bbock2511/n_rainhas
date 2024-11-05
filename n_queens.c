#include <stdio.h>
#include <stdbool.h>

// Faça uma função que recebe uma string com 16 caracteres
// representando um tabuleiro 4x4.
// Cada caractere da string representa uma posição do tabuleiro,
// podendo ser '.' ou 'X', respectivamente dizendo se a casa está vazia
// ou ocupada por uma rainha.
// A função deve retornar true se tem 4 rainhas e nenhuma está ameaçando
// nenhuma outra, pelas regras de movimentação da rainha do xadrez.

void printtab(char tab[])
{
  for (int i = 0; i < 16; i++) {
    printf("%c ", tab[i]);
    if (i % 4 == 3) putchar('\n');
  }
}

bool problema_na_linha(char tab[], int lin)
{
  // nrainhas = quantas rainhas tem na linha lin
  int nrainhas = 0;
  int pos = lin * 4;
  for (int i = 0; i < 4; i++) {
    if (tab[pos] == 'X') nrainhas++;
    pos++;
  }
  return nrainhas != 1;
}

bool problema_nas_linhas(char tab[]) // exatamente uma rainha em cada linha
{
  for (int i = 0; i < 4; i++) {
    if (problema_na_linha(tab, i)) return true;
  }
  return false;
}

bool problema_nas_colunas(char tab[]) // exatamente uma em cada coluna
{
  // Para cada coluna (de 0 a 3)
  for (int col = 0; col < 4; col++) {
    int nrainhas = 0;
    // Verificar cada linha da coluna
    for (int lin = 0; lin < 4; lin++) {
      if (tab[lin * 4 + col] == 'X') nrainhas++; // Verifica se há uma rainha na posição [lin][col]
    }
    // Se houver mais de uma ou nenhuma rainha na coluna, retorna true (problema)
    if (nrainhas != 1) return true;
  }
  // Se todas as colunas estiverem corretas (exatamente uma rainha em cada coluna), retorna false (sem problema)
  return false;
}

bool problema_nas_diagonais(char tab[]) // no máximo uma em cada diagonal
{
  int nrainhas_main = 0, nrainhas_anti = 0;

  // Verificar a diagonal principal (índices [0,0], [1,1], [2,2], [3,3])
  for (int i = 0; i < 4; i++) {
    if (tab[i * 4 + i] == 'X') nrainhas_main++;
  }
  
  // Verificar a anti-diagonal (índices [0,3], [1,2], [2,1], [3,0])
  for (int i = 0; i < 4; i++) {
    if (tab[i * 4 + (3 - i)] == 'X') nrainhas_anti++;
  }

  // Se houver mais de uma rainha em qualquer diagonal, retorna true (problema)
  if (nrainhas_main > 1 || nrainhas_anti > 1) return true;

  // Se ambas as diagonais tiverem no máximo uma rainha, retorna false (sem problema)
  return false;
}

bool nrainhas(char tab[])
{
  printtab(tab);
  if (problema_nas_linhas(tab)) return false;
  if (problema_nas_colunas(tab)) return false;
  if (problema_nas_diagonais(tab)) return false;
  return true;
}

int main()
{
  if (nrainhas("-X-----XX-----X-")) printf("OK :)\n");
  else printf("NOK :(\n");
  if (nrainhas("-X----X--X----X-")) printf("OK :)\n");
  else printf("NOK :(\n");
  if (nrainhas("-X--X-X--------X")) printf("OK :)\n");
  else printf("NOK :(\n");
  if (nrainhas("-X----X-X------X")) printf("OK :)\n");
  else printf("Não OK :(\n");
}

/* -*-- 
   --*-
   *---
   ---*
*/
