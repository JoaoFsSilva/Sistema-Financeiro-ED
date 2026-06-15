/*
 * =========================================================================
 * INTEGRANTE 1 - OPERAÇÕES DE DESPESA (CRUD)
 * =========================================================================
 */

#include "despesa.h"
#include "../config.h"
#include <iostream>
using namespace std;

// =====================
// VARIÁVEIS GLOBAIS
// =====================
Despesa lista[MAX_DESPESAS];
int quantidade = 0;
int proximoId = 1;

// =====================
// FUNÇÕES AUXILIARES
// =====================

// Busca o índice de uma despesa pelo ID
int buscarIndice(int id) {
    for (int i = 0; i < quantidade; i++) {
        if (lista[i].id == id) return i;
    }
    return -1;
}

// Valida que o valor seja positivo
bool valorValido(float valor) {
    if (valor <= 0) {
        cout << "Erro: O valor deve ser maior que zero!" << endl;
        return false;
    }
    return true;
}

// Valida que descrição e categoria não estejam vazias
bool camposValidos(string descricao, string categoria) {
    if (descricao.empty()) {
        cout << "Erro: A descricao nao pode ser vazia!" << endl;
        return false;
    }
    if (categoria.empty()) {
        cout << "Erro: A categoria nao pode ser vazia!" << endl;
        return false;
    }
    return true;
}

// =====================
// FUNÇÕES DO MOTOR
// =====================

// 1. Inserção Sequencial (Vai para o final da lista)
void inserir(string descricao, string categoria, float valor, string data) {
    if (quantidade >= MAX_DESPESAS) {
        cout << "Erro: Lista cheia!" << endl;
        return;
    }
    if (!camposValidos(descricao, categoria) || !valorValido(valor)) return;

    lista[quantidade].id        = proximoId++;
    lista[quantidade].descricao = descricao;
    lista[quantidade].categoria = categoria;
    lista[quantidade].data      = data;
    lista[quantidade].valor     = valor;
    lista[quantidade].paga      = false;
    quantidade++;
    cout << "Despesa [" << descricao << "] inserida com sucesso!" << endl;
}

// 2. Inserção Ordenada (insere ordenando pelo valor, do maior para o menor)
void inserirOrdenado(string descricao, string categoria, float valor, string data) {
    if (quantidade >= MAX_DESPESAS) {
        cout << "Erro: Lista cheia!" << endl;
        return;
    }
    if (!camposValidos(descricao, categoria) || !valorValido(valor)) return;

    // Encontra a posição correta onde o novo valor deve entrar (descendente)
    int pos = 0;
    while (pos < quantidade && lista[pos].valor > valor) {
        pos++;
    }

    // Desloca os elementos para a direita para abrir espaço
    for (int i = quantidade; i > pos; i--) {
        lista[i] = lista[i - 1];
    }

    // Insere o novo elemento na posição correta
    lista[pos].id        = proximoId++;
    lista[pos].descricao = descricao;
    lista[pos].categoria = categoria;
    lista[pos].data      = data;
    lista[pos].valor     = valor;
    lista[pos].paga      = false;
    quantidade++;
    cout << "Despesa [" << descricao << "] inserida de forma ordenada!" << endl;
}

// 3. Listagem com formatação
void listar() {
    if (quantidade == 0) {
        cout << "Lista vazia!" << endl;
        return;
    }
    cout << "---------------------------------------------------" << endl;
    for (int i = 0; i < quantidade; i++) {
        cout << "[" << lista[i].id << "] "
             << lista[i].descricao << " (" << lista[i].categoria << ") - R$ "
             << lista[i].valor << " em " << lista[i].data << " "
             << (lista[i].paga ? "(PAGA)" : "(PENDENTE)") << endl;
    }
    cout << "---------------------------------------------------" << endl;
}

// 4. Edição
void editar(int id, string novaDescricao, string novaCategoria, float novoValor, string novaData) {
    if (!camposValidos(novaDescricao, novaCategoria) || !valorValido(novoValor)) return;

    int idx = buscarIndice(id);
    if (idx == -1) {
        cout << "ID " << id << " nao encontrado para edicao!" << endl;
        return;
    }

    lista[idx].descricao = novaDescricao;
    lista[idx].categoria = novaCategoria;
    lista[idx].data      = novaData;
    lista[idx].valor     = novoValor;
    cout << "Despesa " << id << " editada com sucesso!" << endl;
}

// 5. Remoção
void remover(int id) {
    int idx = buscarIndice(id);
    if (idx == -1) {
        cout << "ID " << id << " nao encontrado para remocao!" << endl;
        return;
    }
    // Desloca os elementos para a esquerda para cobrir o "buraco"
    for (int j = idx; j < quantidade - 1; j++) {
        lista[j] = lista[j + 1];
    }
    quantidade--;
    cout << "Despesa " << id << " removida com sucesso!" << endl;
}

// 6. Busca por categoria
void buscarPorCategoria(string categoria) {
    bool encontrou = false;
    cout << "--- Despesas na categoria [" << categoria << "] ---" << endl;
    for (int i = 0; i < quantidade; i++) {
        if (lista[i].categoria == categoria) {
            cout << "[" << lista[i].id << "] "
                 << lista[i].descricao << " - R$ "
                 << lista[i].valor << " em " << lista[i].data << " "
                 << (lista[i].paga ? "(PAGA)" : "(PENDENTE)") << endl;
            encontrou = true;
        }
    }
    if (!encontrou) cout << "Nenhuma despesa encontrada nessa categoria." << endl;
    cout << "---------------------------------------------------" << endl;
}

// 7. Total por categoria
float totalPorCategoria(string categoria) {
    float total = 0.0f;
    for (int i = 0; i < quantidade; i++) {
        if (lista[i].categoria == categoria) {
            total += lista[i].valor;
        }
    }
    return total;
}

// 8. Marcar como paga
void marcarComoPaga(int id) {
    int idx = buscarIndice(id);
    if (idx == -1) {
        cout << "ID " << id << " nao encontrado!" << endl;
        return;
    }
    lista[idx].paga = true;
    cout << "Despesa " << id << " marcada como paga!" << endl;
}