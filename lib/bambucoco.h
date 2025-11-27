typedef struct ItemCardapio {
  int id;
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
