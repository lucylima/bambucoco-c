#ifndef BAMBUCOCO_H
#define BAMBUCOCO_H

#include <stdio.h>
#define MAX_COLUNAS 5
#define MAX_LINHAS 5

typedef struct ItemCardapio {
  int id_cardapio;
  char nome[30];
  float preco;
} ItemCardapio;

typedef struct Pedido {
  int id_item;
  char nome[30];
  float preco;
  int quantidade;
} Pedido;

typedef struct Mesa {
  int id_mesa;
  char status;
  float valor_total;
  Pedido *comanda;
  char capacidade;
  int tam_comanda;
} Mesa;

void add_cardapio(FILE *arquivo);
void limpar_buffer();
void bootstrap_restaurante(Mesa r[MAX_LINHAS][MAX_COLUNAS]);

#endif // BAMBUCOCO_H
