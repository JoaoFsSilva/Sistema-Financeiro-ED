/*
 * =========================================================================
 * INTEGRANTE 1 - ESTRUTURA E PROTÓTIPOS DE DESPESA
 * =========================================================================
 */

#ifndef DESPESA_H
#define DESPESA_H

#include "../config.h"
#include <string>
using namespace std;

struct Despesa {
    int    id;
    string descricao;
    string categoria;
    string data;
    float  valor;
    bool   paga;
};

// ====== VARIÁVEIS GLOBAIS (Integrante 1) ======
extern Despesa lista[MAX_DESPESAS];
extern int quantidade;
extern int proximoId;

// ====== FUNÇÕES CRUD (Integrante 1) ======
void inserir(string descricao, string categoria, float valor, string data);
void inserirOrdenado(string descricao, string categoria, float valor, string data);
void listar();
void editar(int id, string novaDescricao, string novaCategoria, float novoValor, string novaData);
void remover(int id);
void buscarPorCategoria(string categoria);
float totalPorCategoria(string categoria);
void marcarComoPaga(int id);
int buscarIndice(int id);

#endif // DESPESA_H