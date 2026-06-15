#include "relatorios.h"
#include "interface.h"
#include "../models/despesa.h"
#include <cstdio>

void desenharRelatorio(Sistema& s) {
    int ox = 200, oy = 20;
    DrawText("Relatorio por Categoria", ox, oy, 26, COR_TEXTO);
    DrawLine(ox, oy + 34, LARGURA_TELA - 20, oy + 34, COR_BORDA);

    // Calcula totais
    float totais[NUM_CATEGORIAS] = {};
    float geral = 0;
    for (int i = 0; i < NUM_CATEGORIAS; i++) {
        totais[i] = totalPorCategoria(CATEGORIAS[i]);
        geral += totais[i];
    }

    // Cards resumo
    char buf[64];
    snprintf(buf, sizeof(buf), "R$ %.2f", geral);
    metricaCard("Total geral", buf, ox, oy + 50, 220, 80, COR_ACENTO);

    int pagas = 0, pendentes = 0;
    for (int i = 0; i < quantidade; i++) {
        if (lista[i].paga) pagas++; else pendentes++;
    }
    snprintf(buf, sizeof(buf), "%d despesas", pagas);
    metricaCard("Pagas", buf, ox + 240, oy + 50, 180, 80, COR_ACENTO);
    snprintf(buf, sizeof(buf), "%d despesas", pendentes);
    metricaCard("Pendentes", buf, ox + 440, oy + 50, 180, 80, COR_PERIGO);

    // Barras horizontais
    DrawText("Gasto por categoria", ox, oy + 150, 16, COR_TEXTO2);

    static Color cores[] = {COR_ACENTO, COR_ACENTO2, COR_AVISO, COR_PERIGO,
                             (Color){168,85,247,255}, (Color){20,184,166,255}};

    int barW = 600;
    for (int i = 0; i < NUM_CATEGORIAS; i++) {
        int by = oy + 176 + i * 68;

        DrawText(CATEGORIAS[i], ox, by + 6, 15, COR_TEXTO);

        snprintf(buf, sizeof(buf), "R$ %.2f", totais[i]);
        DrawText(buf, ox + 140, by + 6, 15, cores[i % 6]);

        // Barra de fundo
        DrawRectangle(ox, by + 28, barW, 22, COR_CARD);

        // Barra preenchida
        if (geral > 0) {
            int fill = (int)(totais[i] / geral * barW);
            if (fill > 0)
                DrawRectangleRounded({(float)ox, (float)(by + 28), (float)fill, 22},
                                     0.3f, 4, cores[i % 6]);
        }

        snprintf(buf, sizeof(buf), "%.1f%%", geral > 0 ? (totais[i] / geral * 100.0f) : 0.0f);
        DrawText(buf, ox + barW + 10, by + 30, 14, COR_TEXTO2);
    }

    if (quantidade == 0)
        DrawText("Cadastre despesas para ver o relatorio.", ox, oy + 200, 16, COR_TEXTO2);
}
