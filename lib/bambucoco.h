#ifndef BAMBUCOCO_H
#define BAMBUCOCO_H

typedef struct ItemCardapio {
  int id_cardapio;
  char nome[30];
  float preco;
} ItemCardapio;

typedef struct Pedido {
  int id_item;
  int quantidade;
} Pedido;

typedef struct Mesa {
  int id_mesa;
  char status;
  float valor_total;
  Pedido comanda[10];
} Mesa;

void add_cardapio();
void limpar_buffer();

#endif // BAMBUCOCO_H
