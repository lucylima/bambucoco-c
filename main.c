#include "./lib/interface.h"
#include <stdio.h>

int main(void) {
  char op;

  while (1) {

    if (menu() == 1) {
      return 1;
    }
    menu();
    scanf("%c", &op);
  }

  return 0;
}
