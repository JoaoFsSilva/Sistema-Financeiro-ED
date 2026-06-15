 * =========================================================================
 * INTEGRANTE 4 - IMPLEMENTAÇÃO DA INTERFACE RAYLIB
 * =========================================================================
 */

#include "interface.h"
#include "relatorios.h"
#include "../models/despesa.h"
#include "../structures/historico.h"
#include "../structures/fila.h"
#include "../algorithms/ordenacao.h"
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

// ============================================================
// PRIMITIVOS DE UI
// ============================================================

bool botao(const char* texto, int x, int y, int w, int h,
           Color corFundo, Color corTexto) {
    Rectangle r = {(float)x, (float)y, (float)w, (float)h};
    bool hover  = CheckCollisionPointRec(GetMousePosition(), r);
    bool clique = hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    Color fundo = hover ? COR_HOVER : corFundo;
    DrawRectangleRounded(r, 0.20f, 6, fundo);
    DrawRectangleRoundedLines(r, 0.20f, 6, COR_BORDA);

    int tw = MeasureText(texto, 16);
    DrawText(texto, x + (w - tw) / 2, y + (h - 16) / 2, 16, corTexto);
    return clique;
}

bool campoTexto(char* buffer, int maxLen, int x, int y, int w, int h,
                bool ativo, const char* placeholder) {
    Rectangle r = {(float)x, (float)y, (float)w, (float)h};
    bool clique = CheckCollisionPointRec(GetMousePosition(), r)
                  && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    Color fundoCor = ativo ? COR_INPUT_ATIVO : COR_CARD;
    Color bordaCor = ativo ? COR_ACENTO      : COR_BORDA;

    DrawRectangleRounded(r, 0.12f, 6, fundoCor);
    DrawRectangleRoundedLines(r, 0.12f, 6, bordaCor);

    bool vazio = (buffer[0] == '\0');
    const char* exibir  = vazio ? placeholder : buffer;
    Color corTexto       = vazio ? COR_TEXTO2  : COR_TEXTO;
    DrawText(exibir, x + 10, y + (h - 16) / 2, 16, corTexto);

    if (ativo && !vazio && ((int)(GetTime() * 2) % 2 == 0)) {
        int cx = x + 10 + MeasureText(buffer, 16) + 2;
        DrawLine(cx, y + 8, cx, y + h - 8, COR_TEXTO);
    }

    if (ativo) {
        int key = GetCharPressed();
        while (key > 0) {
            int len = (int)strlen(buffer);
            if (len < maxLen - 1 && key >= 32) {
                buffer[len]     = (char)key;
                buffer[len + 1] = '\0';
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && strlen(buffer) > 0) {
            buffer[strlen(buffer) - 1] = '\0';
        }
    }
    return clique;
}

void metricaCard(const char* label, const char* valor,
                 int x, int y, int w, int h, Color corValor) {
    Rectangle r = {(float)x, (float)y, (float)w, (float)h};
    DrawRectangleRounded(r, 0.12f, 6, COR_CARD);
    DrawRectangleRoundedLines(r, 0.12f, 6, COR_BORDA);
    DrawText(label, x + 16, y + 14, 14, COR_TEXTO2);
    DrawText(valor, x + 16, y + 38, 22, corValor);
}

void setMensagem(Sistema& s, const char* msg) {
    strncpy(s.msgSistema, msg, sizeof(s.msgSistema) - 1);
    s.msgTimer = 3.0f;
}

void mensagemSistema(Sistema& s) {
    if (s.msgTimer <= 0) return;
    s.msgTimer -= GetFrameTime();
    int tw = MeasureText(s.msgSistema, 16);
    int px = (LARGURA_TELA - tw - 32) / 2;
    DrawRectangle(px, ALTURA_TELA - 60, tw + 32, 40, COR_ACENTO);
    DrawText(s.msgSistema, px + 16, ALTURA_TELA - 48, 16, COR_FUNDO);
}

// ============================================================
// BARRA LATERAL
// ============================================================

static const char* ICONES_TELA[] = {"Menu","Novo","Historico","Busca","Relatorio","Pendentes"};

void barraLateral(Sistema& s) {
    DrawRectangle(0, 0, 180, ALTURA_TELA, COR_CARD);
    DrawLine(180, 0, 180, ALTURA_TELA, COR_BORDA);

    DrawText("Financas", 16, 24, 20, COR_ACENTO);
    DrawText("Pessoais", 16, 46, 20, COR_ACENTO);

    for (int i = 0; i < 6; i++) {
        int y = 100 + i * 52;
        bool sel = (s.telaAtual == (Tela)i);
        if (sel) DrawRectangle(0, y - 4, 176, 44, COR_HOVER);
        if (sel) DrawRectangle(0, y - 4, 4, 44, COR_ACENTO);

        Color cor = sel ? COR_ACENTO : COR_TEXTO2;
        DrawText(ICONES_TELA[i], 20, y + 10, 15, cor);

        Rectangle r = {0, (float)(y - 4), 176, 44};
        if (CheckCollisionPointRec(GetMousePosition(), r)
            && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            s.telaAtual = (Tela)i;
            // Reset busca ao trocar de tela
            if (i == 3) {
                s.inputBusca[0]  = '\0';
                s.resultadoBusca = -1;
            }
        }
    }
}

// ============================================================
// TELA MENU (Dashboard)
// ============================================================

void desenharMenu(Sistema& s) {
    int ox = 200, oy = 20;

    DrawText("Dashboard", ox, oy, 26, COR_TEXTO);
    DrawLine(ox, oy + 34, LARGURA_TELA - 20, oy + 34, COR_BORDA);

    // Cards de métricas
    char buf[64];
    snprintf(buf, sizeof(buf), "%d", quantidade);
    metricaCard("Total de despesas", buf, ox, oy + 50, 230, 90, COR_TEXTO);

    float total = 0;
    for (int i = 0; i < quantidade; i++) total += lista[i].valor;
    snprintf(buf, sizeof(buf), "R$ %.2f", total);
    metricaCard("Gasto total", buf, ox + 250, oy + 50, 230, 90, COR_ACENTO);

    int pagas = 0;
    for (int i = 0; i < quantidade; i++) if (lista[i].paga) pagas++;
    snprintf(buf, sizeof(buf), "%d pagas / %d pend.", pagas, quantidade - pagas);
    metricaCard("Status", buf, ox + 500, oy + 50, 270, 90, COR_AVISO);

    snprintf(buf, sizeof(buf), "%d na fila", quantidadePendentes());
    metricaCard("Fila de pagamento", buf, ox + 790, oy + 50, 210, 90, COR_ACENTO2);

    // Lista recente
    DrawText("Lancamentos recentes", ox, oy + 160, 18, COR_TEXTO2);
    DrawLine(ox, oy + 182, LARGURA_TELA - 20, oy + 182, COR_BORDA);

    int inicio = quantidade - 8;
    if (inicio < 0) inicio = 0;

    for (int i = inicio; i < quantidade; i++) {
        int row = oy + 192 + (i - inicio) * 52;
        Rectangle r = {(float)ox, (float)row, (float)(LARGURA_TELA - ox - 20), 46};
        DrawRectangleRounded(r, 0.10f, 4, COR_CARD);
        DrawRectangleRoundedLines(r, 0.10f, 4, COR_BORDA);

        DrawText(lista[i].descricao.c_str(), ox + 12, row + 8,  16, COR_TEXTO);
        DrawText(lista[i].categoria.c_str(), ox + 12, row + 28, 13, COR_TEXTO2);
        DrawText(lista[i].data.c_str(),      ox + 420, row + 17, 15, COR_TEXTO2);

        snprintf(buf, sizeof(buf), "R$ %.2f", lista[i].valor);
        int vw = MeasureText(buf, 16);
        DrawText(buf, ox + 620 - vw, row + 17, 16, lista[i].paga ? COR_ACENTO : COR_AVISO);

        const char* status = lista[i].paga ? "PAGA" : "PENDENTE";
        Color cStatus      = lista[i].paga ? COR_ACENTO : COR_PERIGO;
        int sw = MeasureText(status, 13);
        DrawRectangleRounded({(float)(LARGURA_TELA - 20 - sw - 20), (float)(row + 12), (float)(sw + 16), 22}, 0.5f, 4, cStatus);
        DrawText(status, LARGURA_TELA - 20 - sw - 12, row + 17, 13, COR_FUNDO);
    }

    if (quantidade == 0) {
        DrawText("Nenhuma despesa cadastrada ainda.", ox, oy + 210, 16, COR_TEXTO2);
    }
}

// ============================================================
// TELA CADASTRO
// ============================================================

void desenharCadastro(Sistema& s) {
    int ox = 200, oy = 20;
    DrawText("Nova Despesa", ox, oy, 26, COR_TEXTO);
    DrawLine(ox, oy + 34, LARGURA_TELA - 20, oy + 34, COR_BORDA);

    int fx = ox + 20, fw = 560;

    // Campos
    DrawText("Descricao", fx, oy + 60, 14, COR_TEXTO2);
    if (campoTexto(s.inputDescricao, 128, fx, oy + 78, fw, 40, s.campoAtivo == 0, "Ex: Supermercado"))
        s.campoAtivo = 0;

    DrawText("Valor (R$)", fx, oy + 134, 14, COR_TEXTO2);
    if (campoTexto(s.inputValor, 16, fx, oy + 152, 200, 40, s.campoAtivo == 1, "0.00"))
        s.campoAtivo = 1;

    DrawText("Data (DD/MM/AAAA)", fx + 220, oy + 134, 14, COR_TEXTO2);
    if (campoTexto(s.inputData, 16, fx + 220, oy + 152, 200, 40, s.campoAtivo == 2, "01/01/2025"))
        s.campoAtivo = 2;

    // Categoria
    DrawText("Categoria", fx, oy + 208, 14, COR_TEXTO2);
    for (int i = 0; i < NUM_CATEGORIAS; i++) {
        int bx = fx + i * 110;
        bool sel = (s.categoriaIdx == i);
        Color cf = sel ? COR_ACENTO : COR_CARD;
        Color ct = sel ? COR_FUNDO  : COR_TEXTO2;
        if (botao(CATEGORIAS[i], bx, oy + 226, 104, 34, cf, ct))
            s.categoriaIdx = i;
    }

    // Botão salvar
    if (botao("Salvar Despesa", fx, oy + 290, 200, 44, COR_ACENTO, COR_FUNDO)) {
        if (s.inputDescricao[0] == '\0') {
            setMensagem(s, "Preencha a descricao!");
        } else if (s.inputValor[0] == '\0') {
            setMensagem(s, "Preencha o valor!");
        } else if (s.inputData[0] == '\0') {
            setMensagem(s, "Preencha a data!");
        } else {
            float val = (float)atof(s.inputValor);
            if (val <= 0) {
                setMensagem(s, "Valor deve ser maior que zero!");
            } else {
                string desc  = s.inputDescricao;
                string categ = CATEGORIAS[s.categoriaIdx];
                string data  = s.inputData;

                // Registra com histórico (pilha do Integrante 3)
                inserirComHistorico(desc, categ, val, data);

                // Se não paga, entra na fila de pendentes automaticamente
                if (quantidade > 0 && !lista[quantidade - 1].paga) {
                    enqueueConta(lista[quantidade - 1]);
                }

                setMensagem(s, "Despesa cadastrada com sucesso!");

                // Limpa campos
                s.inputDescricao[0] = '\0';
                s.inputValor[0]     = '\0';
                s.inputData[0]      = '\0';
                s.campoAtivo        = 0;
            }
        }
    }

    // Botão desfazer
    if (botao("Desfazer ultimo", fx + 220, oy + 290, 180, 44, COR_CARD, COR_AVISO)) {
        if (historicoVazio()) {
            setMensagem(s, "Nada para desfazer.");
        } else {
            desfazerHistorico();
            setMensagem(s, "Operacao desfeita!");
        }
    }

    // Preview da lista
    DrawText("Ultimas despesas", fx, oy + 360, 15, COR_TEXTO2);
    int inicio = quantidade - 5;
    if (inicio < 0) inicio = 0;
    for (int i = inicio; i < quantidade; i++) {
        int row = oy + 382 + (i - inicio) * 46;
        char buf[128];
        snprintf(buf, sizeof(buf), "[%d] %s - R$ %.2f (%s) %s",
                 lista[i].id, lista[i].descricao.c_str(), lista[i].valor,
                 lista[i].categoria.c_str(), lista[i].paga ? "(PAGA)" : "(PENDENTE)");
        DrawText(buf, fx, row, 14, COR_TEXTO2);
    }
    if (quantidade == 0)
        DrawText("Nenhuma despesa ainda.", fx, oy + 382, 14, COR_TEXTO2);
}

// ============================================================
// TELA HISTÓRICO
// ============================================================

void desenharHistorico(Sistema& s) {
    int ox = 200, oy = 20;
    DrawText("Historico de Despesas", ox, oy, 26, COR_TEXTO);
    DrawLine(ox, oy + 34, LARGURA_TELA - 20, oy + 34, COR_BORDA);

    // Botões de ordenação
    DrawText("Ordenar por:", ox, oy + 50, 14, COR_TEXTO2);

    bool b1 = botao("Valor (Bubble)",     ox,       oy + 68, 180, 36, s.ordenacaoAtual == 1 ? COR_ACENTO  : COR_CARD, s.ordenacaoAtual == 1 ? COR_FUNDO : COR_TEXTO);
    bool b2 = botao("ID (Selection)",     ox + 196, oy + 68, 180, 36, s.ordenacaoAtual == 2 ? COR_ACENTO2 : COR_CARD, s.ordenacaoAtual == 2 ? COR_FUNDO : COR_TEXTO);
    bool b3 = botao("Categoria (Insert)", ox + 392, oy + 68, 200, 36, s.ordenacaoAtual == 3 ? COR_AVISO   : COR_CARD, s.ordenacaoAtual == 3 ? COR_FUNDO : COR_TEXTO);
    bool b4 = botao("Desfazer",           ox + 608, oy + 68, 120, 36, COR_CARD, COR_PERIGO);

    if (b1) { bubblesort(lista, quantidade);    s.ordenacaoAtual = 1; setMensagem(s, "Ordenado por valor (Bubble Sort)"); }
    if (b2) { selectionsort(lista, quantidade); s.ordenacaoAtual = 2; setMensagem(s, "Ordenado por ID (Selection Sort)"); }
    if (b3) { insertionsort(lista, quantidade); s.ordenacaoAtual = 3; setMensagem(s, "Ordenado por categoria (Insertion Sort)"); }
    if (b4) {
        if (historicoVazio()) setMensagem(s, "Nada para desfazer.");
        else { desfazerHistorico(); setMensagem(s, "Operacao desfeita!"); }
    }

    // Cabeçalho
    int hy = oy + 116;
    DrawRectangle(ox, hy, LARGURA_TELA - ox - 20, 30, COR_HOVER);
    DrawText("ID",        ox + 10,  hy + 8, 13, COR_TEXTO2);
    DrawText("Descricao", ox + 60,  hy + 8, 13, COR_TEXTO2);
    DrawText("Categoria", ox + 340, hy + 8, 13, COR_TEXTO2);
    DrawText("Data",      ox + 500, hy + 8, 13, COR_TEXTO2);
    DrawText("Valor",     ox + 640, hy + 8, 13, COR_TEXTO2);
    DrawText("Status",    ox + 750, hy + 8, 13, COR_TEXTO2);
    DrawText("Acao",      ox + 880, hy + 8, 13, COR_TEXTO2);

    // Scroll
    int visiveis = 9;
    int maxScroll = quantidade - visiveis;
    if (maxScroll < 0) maxScroll = 0;
    s.scrollHistorico += (int)(-GetMouseWheelMove() * 2);
    if (s.scrollHistorico < 0) s.scrollHistorico = 0;
    if (s.scrollHistorico > maxScroll) s.scrollHistorico = maxScroll;

    for (int i = s.scrollHistorico; i < quantidade && i < s.scrollHistorico + visiveis; i++) {
        int row = hy + 34 + (i - s.scrollHistorico) * 48;
        Rectangle r = {(float)ox, (float)row, (float)(LARGURA_TELA - ox - 20), 44};
        DrawRectangleRounded(r, 0.08f, 4, COR_CARD);
        DrawRectangleRoundedLines(r, 0.08f, 4, COR_BORDA);

        char buf[32];
        snprintf(buf, sizeof(buf), "%d", lista[i].id);
        DrawText(buf, ox + 10, row + 14, 14, COR_TEXTO2);
        DrawText(lista[i].descricao.c_str(), ox + 60,  row + 14, 14, COR_TEXTO);
        DrawText(lista[i].categoria.c_str(), ox + 340, row + 14, 14, COR_TEXTO2);
        DrawText(lista[i].data.c_str(),      ox + 500, row + 14, 14, COR_TEXTO2);

        snprintf(buf, sizeof(buf), "R$ %.2f", lista[i].valor);
        DrawText(buf, ox + 640, row + 14, 14, COR_ACENTO);

        const char* st = lista[i].paga ? "PAGA" : "PEND.";
        Color cs       = lista[i].paga ? COR_ACENTO : COR_PERIGO;
        DrawText(st, ox + 760, row + 14, 13, cs);

        if (botao("X", ox + 880, row + 10, 28, 26, COR_PERIGO, COR_FUNDO)) {
            removerComHistorico(lista[i].id);
            setMensagem(s, "Despesa removida!");
            if (s.scrollHistorico > 0) s.scrollHistorico--;
        }
    }

    if (quantidade == 0)
        DrawText("Nenhuma despesa cadastrada.", ox, hy + 50, 16, COR_TEXTO2);
}

// ============================================================
// TELA BUSCA
// ============================================================

void desenharBusca(Sistema& s) {
    int ox = 200, oy = 20;
    DrawText("Busca por ID", ox, oy, 26, COR_TEXTO);
    DrawLine(ox, oy + 34, LARGURA_TELA - 20, oy + 34, COR_BORDA);

    DrawText("Para usar a busca binaria, a lista deve estar ordenada por ID.", ox, oy + 50, 14, COR_TEXTO2);
    DrawText("Use o botao 'ID (Selection)' na tela Historico primeiro.", ox, oy + 68, 14, COR_AVISO);

    DrawText("ID da despesa:", ox, oy + 106, 14, COR_TEXTO2);
    campoTexto(s.inputBusca, 16, ox, oy + 124, 200, 40, true, "Ex: 3");

    if (botao("Buscar (Binaria)", ox + 216, oy + 124, 180, 40, COR_ACENTO, COR_FUNDO)) {
        int id = atoi(s.inputBusca);
        if (id <= 0) {
            setMensagem(s, "Digite um ID valido.");
            s.resultadoBusca = -1;
        } else {
            // ---- BUSCA BINÁRIA (Integrante 2) ----
            // PRÉ-REQUISITO: lista ordenada por ID via selectionsort
            s.resultadoBusca = buscabinaria(lista, quantidade, id);
            if (s.resultadoBusca == -1)
                setMensagem(s, "ID nao encontrado.");
            else
                setMensagem(s, "Despesa encontrada!");
        }
    }

    if (s.resultadoBusca >= 0 && s.resultadoBusca < quantidade) {
        Despesa& d = lista[s.resultadoBusca];
        int ry = oy + 196;

        DrawText("Resultado:", ox, ry, 16, COR_TEXTO2);
        ry += 24;

        Rectangle card = {(float)ox, (float)ry, 680, 160};
        DrawRectangleRounded(card, 0.10f, 6, COR_CARD);
        DrawRectangleRoundedLines(card, 0.10f, 6, COR_ACENTO);

        char buf[64];
        snprintf(buf, sizeof(buf), "ID: %d", d.id);
        DrawText(buf, ox + 16, ry + 16, 16, COR_TEXTO2);
        DrawText(d.descricao.c_str(),  ox + 16, ry + 44, 20, COR_TEXTO);
        DrawText(d.categoria.c_str(),  ox + 16, ry + 74, 15, COR_TEXTO2);
        DrawText(d.data.c_str(),       ox + 200, ry + 74, 15, COR_TEXTO2);

        snprintf(buf, sizeof(buf), "R$ %.2f", d.valor);
        DrawText(buf, ox + 16, ry + 104, 22, COR_ACENTO);

        const char* st = d.paga ? "PAGA" : "PENDENTE";
        Color cs       = d.paga ? COR_ACENTO : COR_PERIGO;
        DrawText(st, ox + 200, ry + 108, 16, cs);

        snprintf(buf, sizeof(buf), "(indice %d na lista)", s.resultadoBusca);
        DrawText(buf, ox + 400, ry + 108, 13, COR_TEXTO2);

        // Ação rápida
        if (!d.paga && botao("Agendar pagamento", ox + 400, ry + 16, 200, 36, COR_ACENTO2, COR_FUNDO)) {
            agendarPagamentoPorId(d.id);
            setMensagem(s, "Agendado na fila!");
        }
        if (botao("Remover", ox + 400, ry + 60, 120, 36, COR_PERIGO, COR_FUNDO)) {
            removerComHistorico(d.id);
            s.resultadoBusca = -1;
            setMensagem(s, "Despesa removida!");
        }
    }
}

// ============================================================
// TELA PENDENTES (FILA FIFO)
// ============================================================

void desenharPendentes(Sistema& s) {
    int ox = 200, oy = 20;
    DrawText("Fila de Pagamentos (FIFO)", ox, oy, 26, COR_TEXTO);
    DrawLine(ox, oy + 34, LARGURA_TELA - 20, oy + 34, COR_BORDA);

    char buf[64];
    snprintf(buf, sizeof(buf), "%d conta(s) na fila", quantidadePendentes());
    DrawText(buf, ox, oy + 50, 15, COR_TEXTO2);

    if (botao("Pagar proxima (FIFO)", ox, oy + 74, 220, 40, COR_ACENTO, COR_FUNDO)) {
        if (filaVaziaContas()) setMensagem(s, "Fila vazia!");
        else { pagarProximaConta(); setMensagem(s, "Conta paga e removida da fila!"); }
    }

    // Exibe a fila usando a estrutura interna (acesso via função de leitura)
    DrawText("Posicao", ox + 10,  oy + 132, 13, COR_TEXTO2);
    DrawText("ID",      ox + 100, oy + 132, 13, COR_TEXTO2);
    DrawText("Descricao", ox + 150, oy + 132, 13, COR_TEXTO2);
    DrawText("Valor",   ox + 500, oy + 132, 13, COR_TEXTO2);
    DrawText("Data",    ox + 640, oy + 132, 13, COR_TEXTO2);
    DrawLine(ox, oy + 148, LARGURA_TELA - 20, oy + 148, COR_BORDA);

    // Para exibir a fila na tela precisamos acessar as despesas da lista principal
    // que estão pendentes (paga == false), respeitando a ordem de cadastro
    int pos = 1;
    for (int i = 0; i < quantidade && pos <= 12; i++) {
        if (!lista[i].paga) {
            int row = oy + 156 + (pos - 1) * 48;
            Rectangle r = {(float)ox, (float)row, (float)(LARGURA_TELA - ox - 20), 44};

            Color cardCor = (pos == 1) ? (Color){0, 200, 150, 30} : COR_CARD;
            DrawRectangleRounded(r, 0.08f, 4, cardCor);
            DrawRectangleRoundedLines(r, 0.08f, 4, pos == 1 ? COR_ACENTO : COR_BORDA);

            snprintf(buf, sizeof(buf), "#%d", pos);
            DrawText(buf, ox + 10, row + 14, 15, pos == 1 ? COR_ACENTO : COR_TEXTO2);

            snprintf(buf, sizeof(buf), "%d", lista[i].id);
            DrawText(buf, ox + 100, row + 14, 14, COR_TEXTO2);

            DrawText(lista[i].descricao.c_str(), ox + 150, row + 14, 14, COR_TEXTO);

            snprintf(buf, sizeof(buf), "R$ %.2f", lista[i].valor);
            DrawText(buf, ox + 500, row + 14, 14, COR_AVISO);

            DrawText(lista[i].data.c_str(), ox + 640, row + 14, 14, COR_TEXTO2);

            if (pos == 1) DrawText("<-- proxima", ox + 800, row + 14, 13, COR_ACENTO);

            pos++;
        }
    }

    if (quantidadePendentes() == 0)
        DrawText("Nenhuma despesa pendente.", ox, oy + 180, 16, COR_TEXTO2);
}

// ============================================================
// INICIALIZAÇÃO E LOOP
// ============================================================

Sistema iniciarSistema() {
    Sistema s = {};
    s.telaAtual      = TELA_MENU;
    s.rodando        = true;
    s.resultadoBusca = -1;
    s.ordenacaoAtual = 0;
    return s;
}

void desenharInterface(Sistema& s) {
    ClearBackground(COR_FUNDO);

    barraLateral(s);

    switch (s.telaAtual) {
        case TELA_MENU:      desenharMenu(s);      break;
        case TELA_CADASTRO:  desenharCadastro(s);  break;
        case TELA_HISTORICO: desenharHistorico(s); break;
        case TELA_BUSCA:     desenharBusca(s);     break;
        case TELA_RELATORIO: desenharRelatorio(s); break;
        case TELA_PENDENTES: desenharPendentes(s); break;
    }

    mensagemSistema(s);
}
