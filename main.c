#include "./lib/bambucoco.h"
#include "./lib/interface.h"
#include <stdio.h>
#include <stdlib.h>

#define LINHAS 5
#define COLUNAS 5

void limpar_buffer();
void reservar_mesa(Mesa r[LINHAS][COLUNAS]);

int main(void) {
  Mesa restaurante[LINHAS][COLUNAS];
  char op;

  bootstrap_restaurante(restaurante);

  while (1) {
    menu();
    printf(">>> ");
    scanf(" %c", &op);

    switch (op) {

    case '1':
      limpar_buffer();
      interface_restaurante(restaurante);
      printf("Deseja reservar uma mesa? S/n\n>>> ");
      scanf(" %c", &op);

      if (op == 's' || op == 'S') {
        limpar_buffer();
        reservar_mesa(restaurante);
      }

      break;

    case '2':
      limpar_buffer();
      reservar_mesa(restaurante);
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

      switch (op) {
      case '1':
        add_cardapio();
        break;
      case '2':
        break;
      case '3':
        interface_cardapio();
        break;
      }
      break;

    case '6':
      exit(0);
      break;

    default:
      break;
    }
  }

  return 0;
}

void reservar_mesa(Mesa r[LINHAS][COLUNAS]) {
  int input = 0;
  char tam;
  int encontrou = 0;

  interface_restaurante(r);

  printf("Digite a mesa que deseja reservar\n>>> ");
  scanf("%d", &input);

  for (int i = 0; i < LINHAS; i++) {
    for (int j = 0; j < COLUNAS; j++) {

      if (input == r[i][j].id_mesa) {

        encontrou = 1;

        if (r[i][j].status == 'O') {
          printf("mesa ocupada! selecione outra\n");
          reservar_mesa(r);
        }

        printf("Digite o tamanho da mesa:\n");
        printf("P: 10 pedidos\n");
        printf("M: 15 pedidos\n");
        printf("G: 20 pedidos\n>>> ");
        scanf(" %c", &tam);

        switch (tam) {
        case 'P':
          r[i][j].comanda = malloc(sizeof(Pedido) * 10);
          break;
        case 'M':
          r[i][j].comanda = malloc(sizeof(Pedido) * 15);
          break;
        case 'G':
          r[i][j].comanda = malloc(sizeof(Pedido) * 20);
          break;
        }
        r[i][j].status = 'O';
        return;
      }
    }
  }

  if (!encontrou) {
    printf("ID da mesa inexistente... selecione outro\n");
  }
}
