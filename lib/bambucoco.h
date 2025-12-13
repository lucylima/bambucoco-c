#ifndef BAMBUCOCO_H
#define BAMBUCOCO_H

#include <stdio.h>
#include <stdlib.h>
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
  char nome[30];
  float valor_total;
  Pedido *comanda;
  char capacidade;
  int tam_comanda;
  int pos_comanda;
} Mesa;

enum Menu {
  MENU_VER_RESTAURANTE = '1',
  MENU_RESERVAR_MESA = '2',
  MENU_GERENCIAR_COMANDA = '3',
  MENU_PAGAR_CONTA = '4',
  MENU_GERENCIAR_CARDAPIO = '5',
  MENU_SAIR = '6'
};

void limpar_buffer();
void reservar_mesa(Mesa r[MAX_LINHAS][MAX_COLUNAS]);
void add_pedido(Mesa r[MAX_LINHAS][MAX_COLUNAS], int input_produto,
                int input_mesa);
void pagar_conta(Mesa r[MAX_LINHAS][MAX_COLUNAS], int input_mesa);
void salvar_historico(Mesa r, FILE *arquivo);
void add_cardapio(FILE *arquivo);
void limpar_buffer();
void limpar_tela();
void bootstrap_restaurante(Mesa r[MAX_LINHAS][MAX_COLUNAS]);
int carregar_estado_mesa(Mesa r[MAX_LINHAS][MAX_COLUNAS]);
int salvar_estado_mesa(Mesa r[MAX_LINHAS][MAX_COLUNAS]);
void achar_mesa(Mesa r[MAX_LINHAS][MAX_COLUNAS], int input, int *linha,
                int *coluna);
void add_pedido(Mesa r[MAX_LINHAS][MAX_COLUNAS], int input_produto,
                int input_mesa);

#endif // BAMBUCOCO_H
