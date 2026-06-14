/*
 * =========================================================================
 * INTEGRANTE 3 - FILA DE CONTAS PENDENTES (FIFO)
 * =========================================================================
 * Implementação de fila circular para gerenciar despesas pendentes de pagamento.
 * =========================================================================
 */

#include "fila.h"
#include <stdio.h>

// =====================
// FILA CIRCULAR
// =====================
static Despesa filaContas[MAX_PENDENTES];
static int frenteFila = 0;
static int trasFila = 0;
static int tamFila = 0;

// =====================
// FUNÇÕES DA FILA
// =====================

bool filaVaziaContas() {
    return tamFila == 0;
}

static bool filaCheiaContas() {
    return tamFila >= MAX_PENDENTES;
}

// Enfileira uma despesa (adiciona no final)
void enqueueConta(const Despesa* d) {
    if (filaCheiaContas()) {
        printf("Erro: Fila de contas pendentes cheia!\n");
        return;
    }
    
    filaContas[trasFila] = *d;
    trasFila = (trasFila + 1) % MAX_PENDENTES;
    tamFila++;
    printf("Conta [%s] adicionada a fila de pagamentos pendentes.\n", d->descricao);
}

// Desenfileira uma despesa (remove do início)
Despesa dequeueConta() {
    Despesa vazia = {0, "", "", "", 0.0f, false};
    
    if (filaVaziaContas()) {
        printf("Erro: Nenhuma conta pendente na fila.\n");
        return vazia;
    }
    
    Despesa d = filaContas[frenteFila];
    frenteFila = (frenteFila + 1) % MAX_PENDENTES;
    tamFila--;
    return d;
}

// Mostra todas as contas pendentes na fila
void mostrarFilaContas() {
    if (filaVaziaContas()) {
        printf("Fila de pagamentos vazia.\n");
        return;
    }
    
    printf("\n========== FILA DE CONTAS PENDENTES (FIFO) ==========\n");
    printf("Total de contas: %d\n", tamFila);
    printf("---\n");
    
    int tempFrente = frenteFila;
    for (int i = 0; i < tamFila; i++) {
        printf("%d. [ID:%d] %s - R$ %.2f (%s) - %s\n",
               i + 1,
               filaContas[tempFrente].id,
               filaContas[tempFrente].descricao,
               filaContas[tempFrente].valor,
               filaContas[tempFrente].categoria,
               filaContas[tempFrente].data);
        tempFrente = (tempFrente + 1) % MAX_PENDENTES;
    }
    printf("=======================================================\n\n");
}

// Paga a próxima conta da fila
void pagarProximaConta() {
    if (filaVaziaContas()) {
        printf("Nao ha contas para pagar.\n");
        return;
    }
    
    Despesa d = dequeueConta();
    printf("\n>>> PAGANDO: [ID:%d] %s (Valor: R$ %.2f) - Removido da fila.\n\n", 
           d.id, d.descricao, d.valor);
    
    // Marca como paga na lista original
    marcarComoPaga(d.id);
}

// Agendar pagamento para despesa existente pelo id
// Procura a despesa na lista global (de Integrante 1) e a adiciona na fila
void agendarPagamentoPorId(int id) {
    int idx = buscarIndice(id);
    if (idx == -1) {
        printf("Despesa com ID %d nao encontrada para agendamento.\n", id);
        return;
    }
    
    // Verifica se já não está na fila
    int tempFrente = frenteFila;
    for (int i = 0; i < tamFila; i++) {
        if (filaContas[tempFrente].id == id) {
            printf("Despesa ID %d ja esta na fila de pendentes!\n", id);
            return;
        }
        tempFrente = (tempFrente + 1) % MAX_PENDENTES;
    }
    
    // Adiciona à fila
    enqueueConta(&lista[idx]);
}

// Retorna quantas contas estão pendentes na fila
int quantidadePendentes() {
    return tamFila;
}
