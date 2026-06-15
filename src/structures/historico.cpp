/*
 * =========================================================================
 * INTEGRANTE 3 - HISTÓRICO DE OPERAÇÕES (PILHA LIFO)
 * =========================================================================
 */

#include "historico.h"
#include <iostream>
using namespace std;

// =====================
// PILHA DO HISTÓRICO
// =====================
static Operacao pilhaHistorico[MAX_HISTORICO];
static int topoPilha = -1;

// =====================
// FUNÇÕES AUXILIARES
// =====================

static bool pilhaCheia() {
    return topoPilha >= MAX_HISTORICO - 1;
}

bool historicoVazio() {
    return topoPilha == -1;
}

static void pushOperacao(TipoOperacao tipo, const Despesa* despesaAnterior) {
    if (pilhaCheia()) {
        cout << "Aviso: Historico cheio, nao e possivel registrar mais operacoes." << endl;
        return;
    }
    topoPilha++;
    pilhaHistorico[topoPilha].tipo = tipo;
    if (despesaAnterior != nullptr) {
        pilhaHistorico[topoPilha].despesaAnterior = *despesaAnterior;
    }
}

static Operacao popOperacao() {
    if (historicoVazio()) {
        cout << "Erro: Nenhuma operacao no historico para desfazer." << endl;
        Operacao vazia = {};
        vazia.tipo = (TipoOperacao)(-1);
        return vazia;
    }
    return pilhaHistorico[topoPilha--];
}

// =====================
// API DO HISTÓRICO
// =====================

// Wrapper: insere e registra na pilha
void inserirComHistorico(string descricao, string categoria, float valor, string data)  {
    // Chama a função original de Integrante 1
    inserir(descricao, categoria, valor, data);
    pushOperacao(OP_CADASTRO, nullptr);
}

// Wrapper: registra a despesa antes de remover
void removerComHistorico(int id) {
    int idx = buscarIndice(id);
    if (idx == -1) {
        cout << "ID " << id << " nao encontrado para remocao!" << endl;
        return;
    }

    Despesa despesaAnterior = lista[idx];
    remover(id);
    pushOperacao(OP_REMOCAO, &despesaAnterior);
}

// Wrapper: registra mudanças para edição
void editarComHistorico(int id, string novaDescricao, string novaCategoria, float novoValor, string novaData)  {
    int idx = buscarIndice(id);
    if (idx == -1) {
        cout << "ID " << id << " nao encontrado para edicao!" << endl;
        return;
    }

    Despesa despesaAnterior = lista[idx];
    editar(id, novaDescricao, novaCategoria, novoValor, novaData);
    pushOperacao(OP_EDICAO, &despesaAnterior);
}

// Desfaz a última operação
void desfazerHistorico() {
    if (historicoVazio()) {
        cout << "Nada para desfazer!" << endl;
        return;
    }

    Operacao ultima = popOperacao();

    switch (ultima.tipo) {
        case OP_CADASTRO: {
            // Desfazer CADASTRO = remover o último item inserido
            // Não decrementa proximoId — IDs pulados são inofensivos, duplicados causam bugs
            if (quantidade > 0) {
                printf("Desfazendo: Cadastro de [%s]\n", lista[quantidade - 1].descricao);
                quantidade--;
            }
            break;
        }

        case OP_REMOCAO: {
            // Desfazer REMOÇÃO = reinserir o item removido
            if (quantidade < MAX_DESPESAS) {
                cout << "Desfazendo: Remocao de [" << ultima.despesaAnterior.descricao << "]" << endl;
                quantidade++;
            }
            break;
        }

        case OP_EDICAO: {
            // Desfazer EDIÇÃO = restaurar valores anteriores
            int idx = buscarIndice(ultima.despesaAnterior.id);
            if (idx != -1) {
                cout << "Desfazendo: Edicao de [" << ultima.despesaAnterior.descricao << "]" << endl;
                lista[idx] = ultima.despesaAnterior;
            }
            break;
        }

        default:
            cout<<"Operacao desconhecida no historico \n";
    }
}

// Mostrar histórico (debug)
void mostrarHistorico() {
    if (historicoVazio()) {
        cout << "Historico vazio." << endl;
        return;
    }
    cout << "--- HISTORICO DE OPERACOES ---" << endl;
    for (int i = 0; i <= topoPilha; i++) {
        const char* tipoStr;
        switch (pilhaHistorico[i].tipo) {
            case OP_CADASTRO: tipoStr = "CADASTRO"; break;
            case OP_REMOCAO:  tipoStr = "REMOCAO";  break;
            case OP_EDICAO:   tipoStr = "EDICAO";   break;
            default:          tipoStr = "DESCONHECIDO"; break;
        }
        cout << i + 1 << ". " << tipoStr << " - [" << pilhaHistorico[i].despesaAnterior.descricao << "]" << endl;
    }
    cout << "------------------------------" << endl;
}
