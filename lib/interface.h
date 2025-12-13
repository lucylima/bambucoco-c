#ifndef INTERFACE_H
#define INTERFACE_H

#include "bambucoco.h"

void menu();
void interface_restaurante(Mesa m[MAX_LINHAS][MAX_COLUNAS]);
void interface_cardapio();
void interface_imprimir_comanda(Mesa r[MAX_LINHAS][MAX_COLUNAS],
                                int input_mesa);
void limpar_tela();

#endif // INTERFACE_H
