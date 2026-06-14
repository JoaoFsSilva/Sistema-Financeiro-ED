/*
 * =========================================================================
 * INTEGRANTE 3 - HISTÓRICO DE OPERAÇÕES (PILHA LIFO)
 * =========================================================================
 * Implementação de desfazer/refazer operações usando pilha.
 * Trabalha em conjunto com as funções CRUD de Integrante 1.
 * =========================================================================
 */

#include "historico.h"
#include <stdio.h>
#include <string.h>

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
        printf("Aviso: Historico cheio, nao e possivel registrar mais operacoes.\n");
        return;
    }
    topoPilha++;
    pilhaHistorico[topoPilha].tipo = tipo;
    if (despesaAnterior != NULL) {
        pilhaHistorico[topoPilha].despesaAnterior = *despesaAnterior;
    }
}

static Operacao popOperacao() {
    if (historicoVazio()) {
        printf("Erro: Nenhuma operacao no historico para desfazer.\n");
        return {(TipoOperacao)(-1), {0, "", "", "", 0.0f, false}};
    }
    return pilhaHistorico[topoPilha--];
}

// =====================
// API DO HISTÓRICO
// =====================

// Wrapper: insere e registra na pilha
void inserirComHistorico(const char* descricao, const char* categoria, 
                        float valor, const char* data) {
    // Chama a função original de Integrante 1
    inserir(descricao, categoria, valor, data);
    
    // Registra a operação na pilha (sem despesa anterior para CADASTRO)
    pushOperacao(OP_CADASTRO, NULL);
}

// Wrapper: registra a despesa antes de remover, para possibilitar desfazer
void removerComHistorico(int id) {
    int idx = buscarIndice(id);
    if (idx == -1) {
        printf("ID %d nao encontrado para remocao!\n", id);
        return;
    }
    
    // Copia a despesa ANTES de remover (para poder restaurar)
    Despesa despesaAnterior = lista[idx];
    
    // Chama a função original de Integrante 1
    remover(id);
    
    // Registra a operação com a cópia da despesa
    pushOperacao(OP_REMOCAO, &despesaAnterior);
}

// Wrapper: registra mudanças para edição
void editarComHistorico(int id, const char* novaDescricao, const char* novaCategoria,
                       float novoValor, const char* novaData) {
    int idx = buscarIndice(id);
    if (idx == -1) {
        printf("ID %d nao encontrado para edicao!\n", id);
        return;
    }
    
    // Copia o estado anterior para poder restaurar
    Despesa despesaAnterior = lista[idx];
    
    // Chama a função original de Integrante 1
    editar(id, novaDescricao, novaCategoria, novoValor, novaData);
    
    // Registra a operação com a cópia do estado anterior
    pushOperacao(OP_EDICAO, &despesaAnterior);
}

// Desfaz a última operação realizada
void desfazerHistorico() {
    if (historicoVazio()) {
        printf("Nada para desfazer!\n");
        return;
    }

    Operacao ultima = popOperacao();
    
    switch (ultima.tipo) {
        case OP_CADASTRO: {
            // Desfazer CADASTRO = remover o último item inserido
            if (quantidade > 0) {
                printf("Desfazendo: Cadastro de [%s]\n", 
                       lista[quantidade - 1].descricao);
                quantidade--;
                proximoId--;
            }
            break;
        }
        
        case OP_REMOCAO: {
            // Desfazer REMOÇÃO = reinserir o item removido
            if (quantidade < MAX_DESPESAS) {
                printf("Desfazendo: Remocao de [%s]\n", 
                       ultima.despesaAnterior.descricao);
                lista[quantidade] = ultima.despesaAnterior;
                quantidade++;
            }
            break;
        }
        
        case OP_EDICAO: {
            // Desfazer EDIÇÃO = restaurar os valores anteriores
            int idx = buscarIndice(ultima.despesaAnterior.id);
            if (idx != -1) {
                printf("Desfazendo: Edicao de [%s]\n", 
                       ultima.despesaAnterior.descricao);
                lista[idx] = ultima.despesaAnterior;
            }
            break;
        }
        
        default:
            printf("Operacao desconhecida no historico!\n");
    }
}

// Mostrar histórico (para debug)
void mostrarHistorico() {
    if (historicoVazio()) {
        printf("Historico vazio.\n");
        return;
    }
    printf("--- HISTORICO DE OPERACOES ---\n");
    for (int i = 0; i <= topoPilha; i++) {
        const char* tipoStr;
        switch (pilhaHistorico[i].tipo) {
            case OP_CADASTRO: tipoStr = "CADASTRO"; break;
            case OP_REMOCAO: tipoStr = "REMOCAO"; break;
            case OP_EDICAO: tipoStr = "EDICAO"; break;
            default: tipoStr = "DESCONHECIDO"; break;
        }
        printf("%d. %s - [%s]\n", i + 1, tipoStr, 
               pilhaHistorico[i].despesaAnterior.descricao);
    }
    printf("------------------------------\n");
}
