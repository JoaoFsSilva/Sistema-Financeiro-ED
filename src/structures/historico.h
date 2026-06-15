/*
 * =========================================================================
 * INTEGRANTE 3 - HEADER DE HISTÓRICO (PILHA LIFO)
 * =========================================================================
 */

#ifndef HISTORICO_H
#define HISTORICO_H

#include "../models/despesa.h"
#include "../models/operacao.h"
#include <string>
using namespace std;

// ====== FUNÇÕES DO HISTÓRICO (Integrante 3) ======

// Wrapper com histórico para inserção
void inserirComHistorico(string descricao, string categoria, 
                        float valor, string data);

// Wrapper com histórico para remoção
void removerComHistorico(int id);

// Wrapper com histórico para edição
void editarComHistorico(int id, string novaDescricao, string novaCategoria,
                       float novoValor, string novaData);

// Desfaz a última operação
void desfazerHistorico();

// Verifica se histórico está vazio
bool historicoVazio();

// Debug: mostra histórico
void mostrarHistorico();

#endif // HISTORICO_H