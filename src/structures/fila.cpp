/*
 * =========================================================================
 * INTEGRANTE 3 - FILA DE CONTAS PENDENTES (FIFO)
 * =========================================================================
 */

#include "fila.h"
#include <iostream>
using namespace std;

// fila circular de despesas pendentes
static Despesa filaContas[MAX_PENDENTES];
static int frenteFila = 0;
static int trasFila   = 0;
static int tamFila    = 0;

// verifica se a fila esta vazia
bool filaVaziaContas() {
    return tamFila == 0;
}

// verifica se a fila esta cheia
static bool filaCheiaContas() {
    return tamFila >= MAX_PENDENTES;
}

// adiciona despesa no final da fila
void enqueueConta(const Despesa& d) {
    if (filaCheiaContas()) {
        cout << "Erro: Fila de contas pendentes cheia!" << endl;
        return;
    }
    filaContas[trasFila] = d;
    trasFila = (trasFila + 1) % MAX_PENDENTES;
    tamFila++;
    cout << "Conta [" << d.descricao << "] adicionada a fila de pagamentos pendentes." << endl;
}

// remove e retorna a despesa do inicio da fila
Despesa dequeueConta() {
    Despesa vazia = {0, "", "", "", 0.0f, false};

    if (filaVaziaContas()) {
        cout << "Erro: Nenhuma conta pendente na fila." << endl;
        return vazia;
    }

    Despesa d = filaContas[frenteFila];
    frenteFila = (frenteFila + 1) % MAX_PENDENTES;
    tamFila--;
    return d;
}

// exibe todas as contas pendentes na fila
void mostrarFilaContas() {
    if (filaVaziaContas()) {
        cout << "Fila de pagamentos vazia." << endl;
        return;
    }

    cout << "\n========== FILA DE CONTAS PENDENTES (FIFO) ==========" << endl;
    cout << "Total de contas: " << tamFila << endl;
    cout << "---" << endl;

    int tempFrente = frenteFila;
    for (int i = 0; i < tamFila; i++) {
        cout << i + 1 << ". [ID:" << filaContas[tempFrente].id << "] "
             << filaContas[tempFrente].descricao << " - R$ "
             << filaContas[tempFrente].valor << " ("
             << filaContas[tempFrente].categoria << ") - "
             << filaContas[tempFrente].data << endl;
        tempFrente = (tempFrente + 1) % MAX_PENDENTES;
    }
    cout << "======================================================\n" << endl;
}

// paga a proxima conta da fila e marca como paga na lista
void pagarProximaConta() {
    if (filaVaziaContas()) {
        cout << "Nao ha contas para pagar." << endl;
        return;
    }

    Despesa d = dequeueConta();
    cout << "\n>>> PAGANDO: [ID:" << d.id << "] " << d.descricao
         << " (Valor: R$ " << d.valor << ") - Removido da fila.\n" << endl;

    marcarComoPaga(d.id);
}

// agenda pagamento de despesa existente pelo ID
void agendarPagamentoPorId(int id) {
    int idx = buscarIndice(id);
    if (idx == -1) {
        cout << "Despesa com ID " << id << " nao encontrada para agendamento." << endl;
        return;
    }

    // verifica se ja esta na fila
    int tempFrente = frenteFila;
    for (int i = 0; i < tamFila; i++) {
        if (filaContas[tempFrente].id == id) {
            cout << "Despesa ID " << id << " ja esta na fila de pendentes!" << endl;
            return;
        }
        tempFrente = (tempFrente + 1) % MAX_PENDENTES;
    }

    enqueueConta(lista[idx]);
}

// retorna quantas contas estao pendentes na fila
int quantidadePendentes() {
    return tamFila;
}