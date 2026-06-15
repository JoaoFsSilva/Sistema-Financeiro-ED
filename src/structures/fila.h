/*
 * =========================================================================
 * INTEGRANTE 3 - HEADER DE FILA (FIFO)
 * =========================================================================
 */

#ifndef FILA_H
#define FILA_H

#include "../models/despesa.h"
#include "../config.h"

// verifica se fila esta vazia
bool filaVaziaContas();

// adiciona uma despesa a fila (enqueue)
void enqueueConta(const Despesa& d);

// remove a proxima despesa da fila (dequeue)
Despesa dequeueConta();

// mostra todas as contas pendentes
void mostrarFilaContas();

// paga a proxima conta da fila (remove e marca como paga)
void pagarProximaConta();

// agenda pagamento para despesa existente pelo ID
void agendarPagamentoPorId(int id);

// retorna quantidade de contas pendentes
int quantidadePendentes();

#endif // FILA_H