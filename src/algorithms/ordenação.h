#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "../models/despesa.h"

void bubblesort(Despesa lista[], int quantidade);
void selectionsort(Despesa lista[], int quantidade);
void insertionsort(Despesa lista[]);
int buscabinaria(Despesa lista[], int quantidade, int idprocurado);

#endif