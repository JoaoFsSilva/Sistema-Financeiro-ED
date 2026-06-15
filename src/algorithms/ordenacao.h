#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "../models/despesa.h"

// Ordena por valor (crescente)
void bubblesort(Despesa lista[], int quantidade);

// Ordena por ID (crescente)
void selectionsort(Despesa lista[], int quantidade);

// Ordena por categoria (alfabetico)
void insertionsort(Despesa lista[], int quantidade);

// Busca binária por ID — lista deve estar ordenada por ID (use selectionsort antes)
// Retorna índice ou -1 se não encontrado
int buscabinaria(Despesa lista[], int quantidade, int idprocurado);

#endif // ORDENACAO_H
