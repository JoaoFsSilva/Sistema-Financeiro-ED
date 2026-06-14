/*
 * =========================================================================
 * INTEGRANTE 1 - OPERAÇÕES DE DESPESA (CRUD)
 * =========================================================================
 * Implementação das funções de gerenciamento de despesas:
 * - Inserção (sequencial e ordenada)
 * - Edição
 * - Remoção
 * - Listagem
 * - Busca por categoria
 * - Total por categoria
 * =========================================================================
 */

#include "despesa.h"
#include "../config.h"
#include <cstring>
#include <stdio.h>

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
        printf("Erro: O valor deve ser maior que zero!\n");
        return false;
    }
    return true;
}

// Valida que descrição e categoria não estejam vazias
bool camposValidos(const char* descricao, const char* categoria) {
    if (descricao == NULL || descricao[0] == '\0') {
        printf("Erro: A descricao nao pode ser vazia!\n");
        return false;
    }
    if (categoria == NULL || categoria[0] == '\0') {
        printf("Erro: A categoria nao pode ser vazia!\n");
        return false;
    }
    return true;
}

// =====================
// FUNÇÕES DO MOTOR
// =====================

// 1. Inserção Sequencial (Vai para o final da lista)
void inserir(const char* descricao, const char* categoria, float valor, const char* data) {
    if (quantidade >= MAX_DESPESAS) {
        printf("Erro: Lista cheia!\n");
        return;
    }
    if (!camposValidos(descricao, categoria) || !valorValido(valor)) return;

    lista[quantidade].id = proximoId++;
    strncpy(lista[quantidade].descricao, descricao, MAX_DESC - 1);
    lista[quantidade].descricao[MAX_DESC - 1] = '\0';
    
    strncpy(lista[quantidade].categoria, categoria, MAX_CATEG - 1);
    lista[quantidade].categoria[MAX_CATEG - 1] = '\0';
    
    strncpy(lista[quantidade].data, data, MAX_DATA - 1);
    lista[quantidade].data[MAX_DATA - 1] = '\0';
    
    lista[quantidade].valor = valor;
    lista[quantidade].paga = false;
    quantidade++;
    printf("Despesa [%s] inserida com sucesso!\n", descricao);
}

// 2. Inserção Ordenada (insere ordenando pelo valor, do maior para o menor)
void inserirOrdenado(const char* descricao, const char* categoria, float valor, const char* data) {
    if (quantidade >= MAX_DESPESAS) {
        printf("Erro: Lista cheia!\n");
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
    lista[pos].id = proximoId++;
    strncpy(lista[pos].descricao, descricao, MAX_DESC - 1);
    lista[pos].descricao[MAX_DESC - 1] = '\0';
    
    strncpy(lista[pos].categoria, categoria, MAX_CATEG - 1);
    lista[pos].categoria[MAX_CATEG - 1] = '\0';
    
    strncpy(lista[pos].data, data, MAX_DATA - 1);
    lista[pos].data[MAX_DATA - 1] = '\0';
    
    lista[pos].valor = valor;
    lista[pos].paga = false;
    quantidade++;
    printf("Despesa [%s] inserida de forma ordenada!\n", descricao);
}

// 3. Listagem com formatação
void listar() {
    if (quantidade == 0) {
        printf("Lista vazia!\n");
        return;
    }
    printf("---------------------------------------------------\n");
    for (int i = 0; i < quantidade; i++) {
        printf("[%d] %s (%s) - R$ %.2f em %s %s\n",
               lista[i].id,
               lista[i].descricao,
               lista[i].categoria,
               lista[i].valor,
               lista[i].data,
               lista[i].paga ? "(PAGA)" : "(PENDENTE)");
    }
    printf("---------------------------------------------------\n");
}

// 4. Edição
void editar(int id, const char* novaDescricao, const char* novaCategoria, 
            float novoValor, const char* novaData) {
    if (!camposValidos(novaDescricao, novaCategoria) || !valorValido(novoValor)) return;

    int idx = buscarIndice(id);
    if (idx == -1) {
        printf("ID %d nao encontrado para edicao!\n", id);
        return;
    }
    
    strncpy(lista[idx].descricao, novaDescricao, MAX_DESC - 1);
    lista[idx].descricao[MAX_DESC - 1] = '\0';
    
    strncpy(lista[idx].categoria, novaCategoria, MAX_CATEG - 1);
    lista[idx].categoria[MAX_CATEG - 1] = '\0';
    
    strncpy(lista[idx].data, novaData, MAX_DATA - 1);
    lista[idx].data[MAX_DATA - 1] = '\0';
    
    lista[idx].valor = novoValor;
    printf("Despesa %d editada com sucesso!\n", id);
}

// 5. Remoção
void remover(int id) {
    int idx = buscarIndice(id);
    if (idx == -1) {
        printf("ID %d nao encontrado para remocao!\n", id);
        return;
    }
    // Desloca os elementos para a esquerda para cobrir o "buraco"
    for (int j = idx; j < quantidade - 1; j++) {
        lista[j] = lista[j + 1];
    }
    quantidade--;
    printf("Despesa %d removida com sucesso!\n", id);
}

// 6. Busca por categoria
void buscarPorCategoria(const char* categoria) {
    bool encontrou = false;
    printf("--- Despesas na categoria [%s] ---\n", categoria);
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(lista[i].categoria, categoria) == 0) {
            printf("[%d] %s - R$ %.2f em %s %s\n",
                   lista[i].id,
                   lista[i].descricao,
                   lista[i].valor,
                   lista[i].data,
                   lista[i].paga ? "(PAGA)" : "(PENDENTE)");
            encontrou = true;
        }
    }
    if (!encontrou) printf("Nenhuma despesa encontrada nessa categoria.\n");
    printf("---------------------------------------------------\n");
}

// 7. Total por categoria
float totalPorCategoria(const char* categoria) {
    float total = 0.0f;
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(lista[i].categoria, categoria) == 0) {
            total += lista[i].valor;
        }
    }
    return total;
}

// 8. Marcar como paga
void marcarComoPaga(int id) {
    int idx = buscarIndice(id);
    if (idx == -1) {
        printf("ID %d nao encontrado!\n", id);
        return;
    }
    lista[idx].paga = true;
    printf("Despesa %d marcada como paga!\n", id);
}
