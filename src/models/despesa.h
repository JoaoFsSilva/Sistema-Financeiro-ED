/*
 * =========================================================================
 * INTEGRANTE 1 - ESTRUTURA E PROTÓTIPOS DE DESPESA
 * =========================================================================
 */

#ifndef DESPESA_H
#define DESPESA_H

#include "../config.h"
#include <stdbool.h>

struct Despesa {
    int   id;
    char  descricao[MAX_DESC];
    char  categoria[MAX_CATEG];
    char  data[MAX_DATA];
    float valor;
    bool  paga;
};

// ====== VARIÁVEIS GLOBAIS (Integrante 1) ======
extern Despesa lista[MAX_DESPESAS];
extern int quantidade;
extern int proximoId;

// ====== FUNÇÕES CRUD (Integrante 1) ======
void inserir(const char* descricao, const char* categoria, float valor, const char* data);
void inserirOrdenado(const char* descricao, const char* categoria, float valor, const char* data);
void listar();
void editar(int id, const char* novaDescricao, const char* novaCategoria, 
            float novoValor, const char* novaData);
void remover(int id);
void buscarPorCategoria(const char* categoria);
float totalPorCategoria(const char* categoria);
void marcarComoPaga(int id);
int buscarIndice(int id);

#endif // DESPESA_H
