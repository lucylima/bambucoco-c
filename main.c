#include "./lib/bambucoco.h"
#include "./lib/interface.h"
#include <stdio.h>
#include <stdlib.h>

#define LINHAS 5
#define COLUNAS 5

void limpar_buffer();
void reservar_mesa(Mesa r[LINHAS][COLUNAS]);
Mesa buscar_mesa(Mesa r[LINHAS][COLUNAS], int input);

int main(void) {
  Mesa restaurante[LINHAS][COLUNAS];
  char op;

  bootstrap_restaurante(restaurante);

  while (1) {
    system("clear");
    menu();
    printf(">>> ");
    scanf("%c", &op);

    switch (op) {

    case '1':
      limpar_buffer();
      interface_restaurante(restaurante);
      printf("Deseja reservar uma mesa? S/n\n>>> ");
      scanf("%c", &op);

      if (op == 's' || op == 'S') {
        limpar_buffer();
        reservar_mesa(restaurante);
      }

      break;
    case '2':
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
    }
  default:
    break;
  }

  return 0;
}

void reservar_mesa(Mesa r[LINHAS][COLUNAS]) {
  int input = -1;

  while (1) {
    interface_restaurante(r);

    printf("Digite a mesa que deseja reservar\n>>> ");
    scanf("%d", &input);

    Mesa mesa = buscar_mesa(r, input);

    if (mesa.id_mesa == -1) {
      printf("Mesa não encontrada! digite novamente\n");
    }

    if (mesa.status == 'O') {
      printf("Mesa ocupada! escolha outra\n");
    }

    if (mesa.status == 'L') {
      printf("Mesa %d reservada com sucesso\n", mesa.id_mesa);
      mesa.status = 'O';
      return;
    }
  }
}

Mesa buscar_mesa(Mesa r[LINHAS][COLUNAS], int input) {
  Mesa aux;

  aux.status = 'O';
  aux.id_mesa = -1; // id -1 significa que há algo de errado, a mesa não existe
                    // ou esta ocupada

  for (int i = 0; i < LINHAS; i++) {
    for (int j = 0; j < COLUNAS; j++) {
      if (r[i][j].id_mesa == input) {
        return r[i][j];
      }
    }
  }

  return aux;
}
