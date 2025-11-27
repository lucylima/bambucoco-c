#include "bambucoco.h"
#include <stdio.h>
#include <stdlib.h>

void limpar_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
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
