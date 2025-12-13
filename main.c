#include "./lib/bambucoco.h"
#include "./lib/interface.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINHAS 5
#define COLUNAS 5

void limpar_buffer();
void reservar_mesa(Mesa r[LINHAS][COLUNAS]);
void add_pedido(Mesa r[LINHAS][COLUNAS], int input_produto, int input_mesa);
void pagar_conta(Mesa r[LINHAS][COLUNAS], int input_mesa);
void salvar_historico(Mesa r);
void imprimir_comanda(Mesa r[LINHAS][COLUNAS], int input_mesa);

int main(void) {
  FILE *arquivo;
  Mesa restaurante[LINHAS][COLUNAS];
  char op;

  int input_produto, input_mesa = 0;

  setlocale(LC_ALL, "");

  if (!carregar_estado_mesa(restaurante)) {
    bootstrap_restaurante(restaurante);
  }

  while (1) {
    menu();
    printf(">>> ");
    scanf(" %c", &op);

    switch (op) {

    case MENU_VER_RESTAURANTE:
      limpar_buffer();
      interface_restaurante(restaurante);
      printf("Deseja reservar uma mesa? S/n\n>>> ");
      scanf(" %c", &op);

      if (op == 's' || op == 'S') {
        limpar_buffer();
        reservar_mesa(restaurante);
        salvar_estado_mesa(restaurante);
      }

      break;

    case MENU_RESERVAR_MESA:
      limpar_buffer();
      interface_restaurante(restaurante);
      reservar_mesa(restaurante);
      salvar_estado_mesa(restaurante);
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
        imprimir_comanda(restaurante, input_mesa);
        break;
      }

      break;

    case MENU_PAGAR_CONTA:

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
      salvar_estado_mesa(restaurante);
      exit(0);
      break;

    default:
      break;
    }
  }

  return 0;
}

void add_pedido(Mesa r[MAX_LINHAS][MAX_COLUNAS], int input_produto,
                int input_mesa) {
  FILE *arquivo;     // será REMOVIDO
  char linha[200];   // buffer
  Pedido aux_pedido; // struct que vai guardar os dados do pedido achado

  int *pos = NULL; // ponteiro da posição disponivel no vetor
  int l, c;        // linha e coluna da mesa correta, evita usar for

  arquivo = fopen("./data/restaurante/cardapio.csv", "r");

  if (arquivo == NULL) {
    fclose(arquivo);
    return;
  }

  achar_mesa(r, input_mesa, &l, &c);

  while (fgets(linha, sizeof(linha), arquivo)) {

    sscanf(linha, "%d;%30[^;];%f", &aux_pedido.id_item, aux_pedido.nome,
           &aux_pedido.preco);

    if (input_produto == aux_pedido.id_item) {

      *pos = r[l][c].pos_comanda;

      if (r[l][c].status == 'O' && *pos < r[l][c].tam_comanda) {

        strcpy(r[l][c].comanda[*pos].nome, aux_pedido.nome);

        r[l][c].comanda[*pos].preco = aux_pedido.preco;

        printf("id da mesa: %d\nstatus da mesa: Ocupada\nnome do primeiro "
               "pedido: %s\npreço do primeiro pedido: %.2f\nposicao: %d\n",
               r[l][c].id_mesa, r[l][c].comanda[r[l][c].pos_comanda].nome,
               r[l][c].comanda[r[l][c].pos_comanda].preco, r[l][c].pos_comanda);

        *pos = *pos + 1;
      }
    }
  }

  fclose(arquivo);
}

void pagar_conta(Mesa r[LINHAS][COLUNAS], int input_mesa) {
  float preco_total;
  int l, c;

  achar_mesa(r, input_mesa, &l, &c);

  for (int i = 0; i < r[l][c].tam_comanda; i++) {
    r[l][c].valor_total +=
        (r[l][c].comanda[i].preco * r[l][c].comanda[i].quantidade);
  }

  r[l][c].status = 'L';

  salvar_historico(r[l][c]);

  free(r[l][c].comanda);
}

void salvar_historico(Mesa r) {
  FILE *arquivo;

  arquivo = fopen("./data/restaurante/historico.csv", "a+");

  if (arquivo == NULL) {
    perror("erro ao abrir arquivo\n");
    exit(1);
  }

  time_t tempo_atual = time(NULL);
  struct tm *struct_tempo = localtime(&tempo_atual);
  char buffer_tempo[100];

  strftime(buffer_tempo, sizeof(buffer_tempo), "%d/%m/%Y - %H:%M",
           struct_tempo);

  fprintf(arquivo, "id;tamanho;nome;valor_total;data\n");

  fprintf(arquivo, "%d;%d;%s;%.2f;%s\n", r.id_mesa, r.tam_comanda, r.nome,
          r.valor_total, buffer_tempo);

  fclose(arquivo);
}

void imprimir_comanda(Mesa r[LINHAS][COLUNAS], int input_mesa) {
  int l, c = 0;

  achar_mesa(r, input_mesa, &l, &c);

  if (r[l][c].pos_comanda < 1) {
    printf("Sem produtos na comanda\n");
    return;
  }

  printf("+------------------------------------------+\n");
  printf("| ID |    Nome    |   Preco   | Quantidade |\n");
  printf("+------------------------------------------+\n");

  for (int i = 0; i < r[l][c].pos_comanda; i++) {
    printf("%d  -  %s  -  %.2f  -  %d", r[l][c].comanda[i].id_item,
           r[l][c].comanda[i].nome, r[l][c].comanda[i].preco,
           r[l][c].comanda[i].quantidade);
  }
  printf("+------------------------------------------+\n");
}
