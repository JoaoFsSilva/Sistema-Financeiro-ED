* =========================================================================
 * INTEGRANTE 4 - STRUCT AGREGADORA DO SISTEMA
 * =========================================================================
 * Une o estado de UI. Os dados reais vivem nas variáveis globais de despesa.cpp
 * (lista[], quantidade, proximoId) e nas estruturas do Integrante 3.
 */

#ifndef SISTEMA_H
#define SISTEMA_H

#include "../config.h"
#include <string>
using namespace std;

struct Sistema {
    // Navegação
    Tela  telaAtual;

    // Feedback ao usuário
    char  msgSistema[256];
    float msgTimer;          // segundos restantes para exibir a mensagem

    // Estado da tela de cadastro
    char  inputDescricao[128];
    char  inputValor[16];
    char  inputData[16];
    int   categoriaIdx;      // índice em CATEGORIAS[]
    int   campoAtivo;        // 0=desc, 1=valor, 2=data

    // Estado da tela de busca
    char  inputBusca[16];    // ID digitado
    int   resultadoBusca;    // índice encontrado (-1 = nenhum)

    // Estado da tela de histórico
    int   ordenacaoAtual;    // 0=nenhuma, 1=bubble(valor), 2=selection(id), 3=insertion(categ)
    int   scrollHistorico;

    // Estado da tela de pendentes
    int   scrollPendentes;

    bool  rodando;
};

#endif // SISTEMA_H