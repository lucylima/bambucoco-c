#include "bambucoco.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limpar_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

void add_cardapio(FILE *arquivo) {
  ItemCardapio aux_cardapio;

  if (arquivo == NULL) {
    printf("erro ao abrir arquivo, abortando\n");
    return;
  }

  printf("Digite o ID do item\n>>> ");
  scanf("%d", &aux_cardapio.id_cardapio);

  limpar_buffer();

  printf("Digite o nome do item\n>>> ");
  fgets(aux_cardapio.nome, sizeof(aux_cardapio.nome), stdin);
  aux_cardapio.nome[strcspn(aux_cardapio.nome, "\n")] = '\0';

  printf("Digite o valor do item com virgula\n>>> ");
  scanf("%f", &aux_cardapio.preco);

  fprintf(arquivo, "%d;%s;%.2f\n", aux_cardapio.id_cardapio, aux_cardapio.nome,
          aux_cardapio.preco);
}

void bootstrap_restaurante(Mesa r[MAX_LINHAS][MAX_COLUNAS]) {
  int contador = 1;
  for (int i = 0; i < MAX_LINHAS; i++) {
    for (int j = 0; j < MAX_COLUNAS; j++) {
      r[i][j].id_mesa = contador++;
      r[i][j].status = 'L';
    }
  }
}

void reservar_mesa(Mesa r[MAX_LINHAS][MAX_COLUNAS]) {
  int result, input = 0;
  char tam;

  while (1) {
    printf("Digite a mesa que deseja reservar\n>>> ");
    result = scanf("%d", &input);

    if (result == 1) {
      if (input < 1 || input > (MAX_COLUNAS * MAX_LINHAS)) {
        printf("Mesa fora do limite\n");
        continue;
      }
    }

    if (result != 1 || result == EOF) {
      printf("Por favor, digite um número de 1 a %d\n",
             MAX_LINHAS * MAX_COLUNAS);
      limpar_buffer();
      continue;
    }

    break;
  }

  for (int i = 0; i < MAX_LINHAS; i++) {
    for (int j = 0; j < MAX_COLUNAS; j++) {

      if (input == r[i][j].id_mesa) {

        if (r[i][j].status == 'O') {
          printf("mesa ocupada! selecione outra\n");
          reservar_mesa(r);
        }

        while (1) {
          printf("Digite o tamanho da mesa:\n");
          printf("P: 4 assentos\n");
          printf("M: 8 assentos\n");
          printf("G: 12 assentos\n>>> ");
          scanf(" %c", &tam);

          tam = toupper(tam);

          if (tam != 'G' && tam != 'M' && tam != 'P') {
            printf("tamanho errado! digite uma opção correta\n");
            continue;
          }

          break;
        }

        switch (tam) {
        case 'P':
          r[i][j].comanda = malloc(sizeof(Pedido) * 4);
          r[i][j].tam_comanda = 4;
          printf("Mesa reservada com sucesso\n");
          break;

        case 'M':
          r[i][j].comanda = malloc(sizeof(Pedido) * 8);
          r[i][j].tam_comanda = 8;
          printf("Mesa reservada com sucesso\n");
          break;

        case 'G':
          r[i][j].comanda = malloc(sizeof(Pedido) * 12);
          r[i][j].tam_comanda = 12;
          printf("Mesa reservada com sucesso\n");
          break;
        }

        r[i][j].status = 'O';
        return;
      }
    }
  }
}

int carregar_estado_mesa(Mesa r[MAX_LINHAS][MAX_COLUNAS]) {
  FILE *arquivo;

  arquivo = fopen("./data/restaurante/mesa.bin", "rb");

  if (arquivo == NULL) {
    return 0;
  }

  size_t result = fread(r, sizeof(Mesa), MAX_LINHAS * MAX_COLUNAS, arquivo);

  fclose(arquivo);

  if (result != MAX_LINHAS * MAX_COLUNAS) {
    return 1;
  }

  return 1;
}

int salvar_estado_mesa(Mesa r[MAX_LINHAS][MAX_COLUNAS]) {
  FILE *arquivo;

  arquivo = fopen("./data/restaurante/mesa.bin", "wb");

  if (arquivo == NULL) {
    return 0;
  }

  size_t result = fwrite(r, sizeof(Mesa), MAX_LINHAS * MAX_COLUNAS, arquivo);

  fclose(arquivo);

  return (result == MAX_LINHAS * MAX_COLUNAS);
}
