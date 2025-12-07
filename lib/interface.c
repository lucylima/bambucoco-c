#include "interface.h"
#include "bambucoco.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu() { // funcao que imprime um menu simples em ASCII
  FILE *arq;

  char buffer[200];

  arq = fopen("./data/interface/menu-ascii.txt", "r");

  // se arquivo esta com problemas o programa nao roda
  if (arq == NULL) {
    printf("Erro ao abrir o arquivo, encerrando\n");
    exit(1);
  }

  while (fgets(buffer, sizeof(buffer), arq) != NULL) {
    printf("%s", buffer);
  }

  printf("\n");

  fclose(arq);
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
  char buffer[1000];
  char *token;

  arquivo = fopen("./data/restaurante/cardapio.csv", "r+");

  if (arquivo == NULL) {
    printf("erro ao abrir arquivo do cardpaio, tente inserir algo primeiro\n");
    return;
  }

  printf("+-----------------------------+\n");
  printf("| ID |    Nome    |   Preco   |\n");
  printf("+-----------------------------+\n");
  while (!feof(arquivo)) {

    fgets(buffer, 1000, arquivo);

    token = strtok(buffer, "; ");

    while (token != NULL) {
      printf("| %s  -  ", token);
      token = strtok(NULL, ";");
      printf("%s - ", token);
      token = strtok(NULL, ";");
      printf("R$%s", token);
      token = strtok(NULL, ";");
    }
  }

  printf("\n\t+-----------------------------+\n");
  fclose(arquivo);
}
