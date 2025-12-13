#include "./lib/bambucoco.h"
#include "./lib/interface.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#define LINHAS 5
#define COLUNAS 5

int main(void) {
  FILE *arquivo;
  Mesa restaurante[LINHAS][COLUNAS];
  char op;

  int input_produto, input_mesa = 0;

  setlocale(LC_ALL, "");

  if (!carregar_estado_mesa(restaurante, arquivo)) {
    bootstrap_restaurante(restaurante);
  }

  while (1) {
    limpar_tela();
    menu();
    printf(">>> ");
    scanf(" %c", &op);

    switch (op) {

    case MENU_VER_RESTAURANTE:
      limpar_tela();
      limpar_buffer();
      interface_restaurante(restaurante);
      printf("Deseja reservar uma mesa? S/n\n>>> ");
      scanf(" %c", &op);

      if (op == 's' || op == 'S') {
        limpar_buffer();
        reservar_mesa(restaurante);
        salvar_estado_mesa(restaurante, arquivo);
      }

      break;

    case MENU_RESERVAR_MESA:
      limpar_tela();
      limpar_buffer();
      interface_restaurante(restaurante);
      reservar_mesa(restaurante);
      salvar_estado_mesa(restaurante, arquivo);
      break;

    case MENU_GERENCIAR_COMANDA:
      printf("Digite uma opção:\n");
      printf("1 - adicionar pedido\n2 - Remover pedido\n");
      printf("3 - Ver pedidos da minha mesa\n");
      printf(">>> ");
      scanf(" %c", &op);

      switch (op) {
      case '1':
        printf("Digite o id do produto: ");
        scanf("%d", &input_produto);
        printf("Digite o id da mesa: ");
        scanf("%d", &input_mesa);

        add_pedido(restaurante, input_produto, input_mesa);
        break;

      case '3':
        printf("Digite o id da mesa: ");
        scanf("%d", &input_mesa);
        interface_imprimir_comanda(restaurante, input_mesa);
        break;
      }

      break;

    case MENU_PAGAR_CONTA:
      printf("Digite o id da mesa: ");
      scanf("%d", &input_mesa);
      pagar_conta(restaurante, input_mesa, arquivo);
      break;

    case MENU_GERENCIAR_CARDAPIO:
      limpar_buffer();
      printf("O que deseja fazer?\n");
      printf("1 - adicionar algo ao cardapio\n2 - remover "
             "algo do cardapio\n3 - ver cardapio\n");
      scanf("%c", &op);

      switch (op) {
      case '1':
        arquivo = fopen("./data/restaurante/cardapio.csv", "a+");
        add_cardapio(arquivo);
        fclose(arquivo);
        break;
      case '2':
        break;
      case '3':
        interface_cardapio();
        break;
      }
      break;

    case MENU_SAIR:
      salvar_estado_mesa(restaurante, arquivo);
      exit(0);
      break;

    default:
      break;
    }
  }

  return 0;
}
