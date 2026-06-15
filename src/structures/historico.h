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

// Wrapper com histórico para inserção
void inserirComHistorico(const string& descricao, const string& categoria,
                         float valor, const string& data);

// Wrapper com histórico para remoção
void removerComHistorico(int id);

// Wrapper com histórico para edição
void editarComHistorico(int id, const string& novaDescricao, const string& novaCategoria,
                        float novoValor, const string& novaData);

// Desfaz a última operação
void desfazerHistorico();

// Verifica se histórico está vazio
bool historicoVazio();

// Debug: mostra histórico
void mostrarHistorico();

#endif // HISTORICO_H
