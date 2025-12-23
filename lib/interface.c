#include "interface.h"
#include "bambucoco.h"
#include <stdio.h>
#include <string.h>

void menu() { // funcao que imprime um menu simples em ASCII
  char *opcoes[] = {
      "Ver restaurante",    "Reservar Mesa",
      "Gerenciar comanda",  "Finalizar e pagar a comanda",
      "Gerenciar cardapio", "Sair",
  };

  printf("╔════════════════════════════════════════════════╗\n");
  printf("║      Menu                                      ║\n");

  for (int i = 0; i < 6; i++) {
    printf("║   %d. %-*s║\n\a", i + 1, 42, opcoes[i]);
  }

  printf("╚════════════════════════════════════════════════╝\n");
}

void interface_restaurante(Mesa m[MAX_LINHAS][MAX_COLUNAS]) {
  // imprimir "cabeçalho" do restaurante
  // os numeros sao pra guiar os usuarios
  printf("\t0         1       2       3       4\n");
  printf("+-----------+-----------+-----------+-----------+\n");
  printf("|        COZINHA        |          BAR          |\n");
  printf("+-----------+-----------+-----------+-----------+\n");

  for (int i = 0; i < MAX_LINHAS; i++) {
    printf("%d  |  ", i);
    for (int j = 0; j < MAX_COLUNAS; j++) {
      printf("[%c %d]\t", m[i][j].status, m[i][j].id_mesa);
    }
    printf("|\n");
  }

  printf("+-----------+-----------+-----------+-----------+\n");
  printf("\t ENTRADA                        CAIXA\n");
  printf("+-----------+-----------+-----------+-----------+\n");
  printf("\"L\" Livre - "
         "\"O\" Ocupado\n");
  printf("+-----------+-----------+-----------+-----------+\n");
}

void interface_cardapio() {
  FILE *arquivo;
  char buffer[200];
  char *token;

  arquivo = fopen("./data/restaurante/cardapio.csv", "r+");

  if (arquivo == NULL) {
    printf("erro ao abrir arquivo do cardpaio, tente inserir algo primeiro\n");
    return;
  }

  printf("+-----------------------------+\n");
  printf("| ID |    Nome    |   Preco   |\n");
  printf("+-----------------------------+\n");

  while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {

    if (feof(arquivo)) {
      break;
    } else if (ferror(arquivo)) {
      printf("um erro ocorreu ao ler o arquivo\n");
      return;
    }

    token = strtok(buffer, ";");

    if (token != NULL) {
      printf("| %s  -  ", token);
      token = strtok(NULL, ";");
      printf("%s - ", token);
      token = strtok(NULL, ";");
      printf("R$%s", token);
      token = strtok(NULL, ";");
    }
  }

  printf("+-----------------------------+\n");
  fclose(arquivo);
}

void interface_imprimir_comanda(Mesa r[MAX_LINHAS][MAX_COLUNAS],
                                int input_mesa) {
  int l, c = 0;

  achar_mesa(r, input_mesa, &l, &c);

  if (r[l][c].pos_comanda < 1) {
    printf("Sem produtos na comanda\n");
    return;
  }

  printf("+------------------------------------------+\n");
  printf("| ID |    Nome    |   Preco   | Quantidade |\n");
  printf("+------------------------------------------+\n");

  for (int i = 0; i < r[l][c].pos_comanda; i++) {
    printf("| %d  -  %s  -  %.2f  -  %d\n", r[l][c].comanda[i].id_item,
           r[l][c].comanda[i].nome, r[l][c].comanda[i].preco,
           r[l][c].comanda[i].quantidade);
  }
  printf("+------------------------------------------+\n");
}

void limpar_tela() { printf("\033[2J\033[H"); }

void interface_imprimir_comanda_id(Mesa r[MAX_LINHAS][MAX_COLUNAS],
                                   int input_mesa) {
  int l, c = 0;

  achar_mesa(r, input_mesa, &l, &c);

  if (r[l][c].status == 'L') {
    printf("Mesa livre, sem comanda\n");
    return;
  }

  if (r[l][c].pos_comanda < 1) {
    printf("Sem produtos na comanda\n");
    return;
  }

  printf("+--------------------------------------------+\n");
  printf("| posicao |   Nome   |  Preco  |  Quantidade |\n");
  printf("+--------------------------------------------+\n");

  for (int i = 0; i < r[l][c].pos_comanda; i++) {
    printf("| %d  -  %s  -  %.2f  -  %d\n", i, r[l][c].comanda[i].nome,
           r[l][c].comanda[i].preco, r[l][c].comanda[i].quantidade);
  }
  printf("+------------------------------------------+\n");
  printf("+ -1 significa que o produto foi removido  +\n");
  printf("+------------------------------------------+\n");
}
