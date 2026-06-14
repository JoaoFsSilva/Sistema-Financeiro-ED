/*
 * =========================================================================
 * INTEGRANTE 3 - HEADER DE FILA (FIFO)
 * =========================================================================
 */

#ifndef FILA_H
#define FILA_H

#include "../models/despesa.h"
#include "../config.h"

// ====== FUNÇÕES DA FILA (Integrante 3) ======

// Verifica se fila está vazia
bool filaVaziaContas();

// Adiciona uma despesa à fila (enqueue)
void enqueueConta(const Despesa* d);

// Remove a próxima despesa da fila (dequeue)
Despesa dequeueConta();

// Mostra todas as contas pendentes
void mostrarFilaContas();

// Paga a próxima conta da fila (remove e marca como paga)
void pagarProximaConta();

// Agendar pagamento para despesa existente pelo ID
// Procura a despesa na lista global e a adiciona na fila
void agendarPagamentoPorId(int id);

// Retorna quantidade de contas pendentes
int quantidadePendentes();

#endif // FILA_H
