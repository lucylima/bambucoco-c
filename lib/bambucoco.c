#include "bambucoco.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void limpar_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

void add_cardapio(FILE *arquivo) {
  ItemCardapio aux_cardapio;

  if (arquivo == NULL) {
    perror("erro ao abrir arquivo, abortando\n");
    exit(EXIT_FAILURE);
  }

  printf("Digite o ID do item\n>>> ");
  scanf("%d", &aux_cardapio.id_cardapio);

  limpar_buffer();

  printf("Digite o nome do item\n>>> ");
  fgets(aux_cardapio.nome, sizeof(aux_cardapio.nome), stdin);
  aux_cardapio.nome[strcspn(aux_cardapio.nome, "\n")] = '\0';

  printf("Digite o valor do item com virgula\n>>> ");
  scanf("%f", &aux_cardapio.preco);

  fprintf(arquivo, "%d;%s;%.2f\n", aux_cardapio.id_cardapio, aux_cardapio.nome,
          aux_cardapio.preco);
}

void bootstrap_restaurante(Mesa r[MAX_LINHAS][MAX_COLUNAS]) {
  int contador = 1;
  for (int i = 0; i < MAX_LINHAS; i++) {
    for (int j = 0; j < MAX_COLUNAS; j++) {
      r[i][j].id_mesa = contador++;
      r[i][j].status = 'L';
      r[i][j].pos_comanda = 0;
      r[i][j].valor_total = 0;
    }
  }
}

void reservar_mesa(Mesa r[MAX_LINHAS][MAX_COLUNAS]) {
  int result, input, l, c = 0;
  char tam;

  while (1) {
    printf("Digite a mesa que deseja reservar\n>>> ");
    result = scanf("%d", &input);

    if (result == 1) {
      if (input < 1 || input > (MAX_COLUNAS * MAX_LINHAS)) {
        printf("Mesa fora do limite\n");
        limpar_buffer();
        continue;
      }
    }

    if (result != 1 || result == EOF) {
      printf("Por favor, digite um número de 1 a %d\n",
             MAX_LINHAS * MAX_COLUNAS);
      limpar_buffer();
      continue;
    }

    break;
  }

  achar_mesa(r, input, &l, &c);

  if (r[l][c].status == 'O') {
    printf("mesa ocupada! selecione outra\n");
    reservar_mesa(r);
  }

  limpar_buffer();
  printf("Digite o nome do responsável pela mesa:\n>>> ");
  fgets(r[l][c].nome, sizeof(r[l][c].nome), stdin);
  r[l][c].nome[strcspn(r[l][c].nome, "\n")] = '\0';

  while (1) {
    printf("Digite o tamanho da mesa:\n");
    printf("P: 4 assentos\n");
    printf("M: 8 assentos\n");
    printf("G: 12 assentos\n>>> ");
    scanf(" %c", &tam);

    tam = toupper(tam);

    if (tam != 'G' && tam != 'M' && tam != 'P') {
      printf("tamanho errado! digite uma opção correta\n");
      continue;
    }

    break;
  }

  switch (tam) {
  case 'P':
    r[l][c].comanda = calloc(sizeof(Pedido), 4);
    r[l][c].tam_comanda = 4;
    printf("Mesa reservada com sucesso\n");
    break;

  case 'M':
    r[l][c].comanda = calloc(sizeof(Pedido), 8);
    r[l][c].tam_comanda = 8;
    printf("Mesa reservada com sucesso\n");
    break;

  case 'G':
    r[l][c].comanda = calloc(sizeof(Pedido), 12);
    r[l][c].tam_comanda = 12;
    printf("Mesa reservada com sucesso\n");
    break;
  }

  r[l][c].pos_comanda = 0;
  r[l][c].status = 'O';
  return;
}

int carregar_estado_mesa(Mesa r[MAX_LINHAS][MAX_COLUNAS]) {
  FILE *arquivo;

  arquivo = fopen("./data/restaurante/mesa.bin", "rb");

  if (arquivo == NULL) {
    return 0;
  }

  for (int i = 0; i < MAX_LINHAS; i++) {
    for (int j = 0; j < MAX_COLUNAS; j++) {

      fread(&r[i][j], sizeof(Mesa), 1, arquivo);

      r[i][j].comanda = NULL;

      if (r[i][j].tam_comanda > 0) {

        r[i][j].comanda = (Pedido *)calloc(sizeof(Pedido), r[i][j].tam_comanda);

        if (r[i][j].comanda == NULL) {
          perror("Erro ao alocar memória\n");
          exit(EXIT_FAILURE);
        }

        fread(r[i][j].comanda, sizeof(Pedido), r[i][j].tam_comanda, arquivo);
      }
    }
  }

  fclose(arquivo);

  return 1;
}

int salvar_estado_mesa(Mesa r[MAX_LINHAS][MAX_COLUNAS]) {
  FILE *arquivo;

  arquivo = fopen("./data/restaurante/mesa.bin", "wb");

  if (arquivo == NULL) {
    perror("Erro ao abrir arquivo\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < MAX_LINHAS; i++) {
    for (int j = 0; j < MAX_COLUNAS; j++) {

      fwrite(&r[i][j], sizeof(Mesa), 1, arquivo);

      if (r[i][j].tam_comanda > 0 && r[i][j].comanda != NULL) {
        fwrite(&r[i][j].comanda, sizeof(Pedido), r[i][j].tam_comanda, arquivo);
      }
    }
  }

  fclose(arquivo);
  return 1;
}

void achar_mesa(Mesa r[MAX_LINHAS][MAX_COLUNAS], int input, int *linha,
                int *coluna) {
  for (int i = 0; i < MAX_LINHAS; i++)
    for (int j = 0; j < MAX_COLUNAS; j++) {
      if (input == r[i][j].id_mesa) {
        *linha = i;
        *coluna = j;
      }
    }
}

void add_pedido(Mesa r[MAX_LINHAS][MAX_COLUNAS], int input_produto,
                int input_mesa, int quantidade) {
  FILE *arquivo;
  char linha[200];
  Pedido aux_pedido;
  int pos;
  int l, c;

  arquivo = fopen("./data/restaurante/cardapio.csv", "r");

  if (arquivo == NULL) {
    perror("Erro ao abrir arquivo\n");
    exit(EXIT_FAILURE);
  }

  achar_mesa(r, input_mesa, &l, &c);

  if (r[l][c].status == 'L') {
    printf("Mesa livre! Reserve a mesa antes de adicionar pedidos.\n");
    return;
  }

  if (r[l][c].pos_comanda >= r[l][c].tam_comanda) {
    printf("Mesa cheia! junte a sua mesa ou reserve outra maior\n");
    return;
  }

  while (fgets(linha, sizeof(linha), arquivo)) {

    sscanf(linha, "%d;%30[^;];%f", &aux_pedido.id_item, aux_pedido.nome,
           &aux_pedido.preco);

    if (input_produto == aux_pedido.id_item) {

      pos = r[l][c].pos_comanda;

      r[l][c].comanda[pos].id_item = aux_pedido.id_item;

      strcpy(r[l][c].comanda[pos].nome, aux_pedido.nome);

      r[l][c].comanda[pos].quantidade = quantidade;

      r[l][c].comanda[pos].preco = aux_pedido.preco;

      r[l][c].pos_comanda++;
    }
  }

  fclose(arquivo);
}

void pagar_conta(Mesa r[MAX_LINHAS][MAX_COLUNAS], int input_mesa,
                 FILE *arquivo) {
  int l, c;

  achar_mesa(r, input_mesa, &l, &c);

  if (r[l][c].status == 'L') {
    printf("Mesa já está livre! Só paga conta de mesa ocupada.\n");
    return;
  }

  if (r[l][c].pos_comanda <= 0) {
    printf("Mesa sem pedidos! Não há nada para pagar.\n");
    return;
  }

  r[l][c].valor_total = 0;

  for (int i = 0; i < r[l][c].pos_comanda; i++) {

    if (r[l][c].comanda[i].id_item == -1 ||
        r[l][c].comanda[i].quantidade == 0) {
      continue;
    }

    r[l][c].valor_total +=
        (r[l][c].comanda[i].preco * r[l][c].comanda[i].quantidade);
  }

  r[l][c].status = 'L';

  salvar_historico(r[l][c], arquivo);

  free(r[l][c].comanda);
}

void salvar_historico(Mesa r, FILE *arquivo) {

  arquivo = fopen("./data/restaurante/historico.csv", "a+");

  if (arquivo == NULL) {
    perror("erro ao abrir arquivo\n");
    exit(EXIT_FAILURE);
  }

  time_t tempo_atual = time(NULL);
  struct tm *struct_tempo = localtime(&tempo_atual);
  char buffer_tempo[100];

  strftime(buffer_tempo, sizeof(buffer_tempo), "%d/%m/%Y %H:%M", struct_tempo);

  fprintf(arquivo, "id;tamanho;nome;valor_total;data\n");

  fprintf(arquivo, "%d;%d;%s;%.2f;%s\n", r.id_mesa, r.tam_comanda, r.nome,
          r.valor_total, buffer_tempo);

  fclose(arquivo);
}

void remover_pedido(Mesa r[MAX_LINHAS][MAX_COLUNAS], int input_mesa,
                    int input_produto) {
  int l, c = 0;

  achar_mesa(r, input_mesa, &l, &c);

  if (r[l][c].status == 'L') {
    printf("Mesa livre! Não há pedidos para remover.\n");
    return;
  }

  if (r[l][c].pos_comanda < 1) {
    printf("Sem produtos na comanda\n");
    return;
  }

  r[l][c].comanda[input_produto].id_item = -1;
  printf("Pedido removido com sucesso\n");
}
