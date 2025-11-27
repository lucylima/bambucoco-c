#include "./lib/bambucoco.h"
#include "./lib/interface.h"
#include <stdio.h>
#include <stdlib.h>

#define LINHAS 5
#define COLUNAS 5

void limpar_buffer();
void bootstrap_restaurante(Mesa r[LINHAS][COLUNAS]);
void reservar_mesa(Mesa r[LINHAS][COLUNAS]);

int main(void) {
  FILE *arquivo;
  Mesa restaurante[LINHAS][COLUNAS];
  char op;

  bootstrap_restaurante(restaurante);

  while (1) {
    menu();
    printf(">>> ");
    scanf("%c", &op);

    switch (op) {

    case '1':
      limpar_buffer();
      interface_restaurante(restaurante, LINHAS, COLUNAS);
      printf("Deseja reservar uma mesa? S/n\n>>> ");
      scanf("%c", &op);

      if (op == 's' || op == 'S') {
        limpar_buffer();
        reservar_mesa(restaurante);
      }

      break;
    case '2':

      break;

    case '3':

      break;

    case '4':

      break;
    case '5':
      limpar_buffer();
      printf("O que deseja fazer?\n1 - adicionar algo ao cardapio\n2 - remover "
             "algo do cardapio\n3 - ver cardapio\n");
      scanf("%c", &op);

      break;

    case '6':
      exit(0);
      break;
    }
  }

  return 0;
}

void add_cardapio() {
  ItemCardapio aux_cardapio;

  FILE *arquivo;

  arquivo = fopen("./data/restaurante/cardapio.dat", "ab+");

  if (arquivo == NULL) {
    printf("erro ao abrir arquivo, abortando\n");
    exit(1);
  }

  printf("Digite o ID do item\n>>> ");
  scanf("%d", &aux_cardapio.id_cardapio);

  printf("Digite o nome do item\n>>> ");
  fgets(aux_cardapio.nome, sizeof(aux_cardapio.nome), stdin);

  printf("Digite o valor do item\n>>> ");
  scanf("%f", &aux_cardapio.preco);

  fwrite(&aux_cardapio, sizeof(ItemCardapio), 1, arquivo);

  fclose(arquivo);
}

void reservar_mesa(Mesa r[LINHAS][COLUNAS]) {
  int i, j = 0;
  interface_restaurante(r, LINHAS, COLUNAS);
  printf("Digite a mesa que deseja reservar, ex 0 1\n>>> ");
  scanf("%d %d", &i, &j);
  r[i][j].status = 'O';
}

void bootstrap_restaurante(Mesa r[LINHAS][COLUNAS]) {
  int contador = 1;
  for (int i = 0; i < LINHAS; i++) {
    for (int j = 0; j < COLUNAS; j++) {
      r[i][j].id_mesa = contador++;
      r[i][j].status = 'L';
    }
  }
}

void limpar_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}
