#include "interface.h"
#include <stdio.h>
#include <stdlib.h>

int menu() {
  FILE *arq;

  char buffer[200];

  arq = fopen("./data/interface/menu-ascii.txt", "r");

  if (arq == NULL) {
    printf("Erro ao abrir o arquivo, encerrando");
    return 1;
  }

  while (fgets(buffer, sizeof(buffer), arq) != NULL) {
    printf("%s", buffer);
  }

  printf("\n");
  printf(">>> ");

  fclose(arq);

  return 0;
}
