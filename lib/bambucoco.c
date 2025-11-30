#include "bambucoco.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limpar_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

void add_cardapio() {
  ItemCardapio aux_cardapio;

  FILE *arquivo;

  arquivo = fopen("./data/restaurante/cardapio.csv", "a+");

  if (arquivo == NULL) {
    printf("erro ao abrir arquivo, abortando\n");
    exit(1);
  }

  printf("Digite o ID do item\n>>> ");
  scanf("%d", &aux_cardapio.id_cardapio);

  limpar_buffer();

  printf("Digite o nome do item\n>>> ");
  fgets(aux_cardapio.nome, sizeof(aux_cardapio.nome), stdin);
  aux_cardapio.nome[strcspn(aux_cardapio.nome, "\n")] = '\0';

  printf("Digite o valor do item\n>>> ");
  scanf("%f", &aux_cardapio.preco);

  fprintf(arquivo, "%d, %s, %.2f\n", aux_cardapio.id_cardapio,
          aux_cardapio.nome, aux_cardapio.preco);

  fclose(arquivo);
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
