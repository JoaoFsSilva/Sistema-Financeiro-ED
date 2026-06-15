 * =========================================================================
 * INTEGRANTE 4 - HEADER DA INTERFACE RAYLIB
 * =========================================================================
 */

#ifndef INTERFACE_H
#define INTERFACE_H

#include "raylib.h"
#include "sistema.h"
#include "../config.h"

// ====== PALETA DE CORES ======
#define COR_FUNDO       (Color){ 15,  17,  23, 255}
#define COR_CARD        (Color){ 26,  29,  46, 255}
#define COR_ACENTO      (Color){  0, 200, 150, 255}
#define COR_ACENTO2     (Color){ 99, 102, 241, 255}
#define COR_PERIGO      (Color){239,  68,  68, 255}
#define COR_AVISO       (Color){245, 158,  11, 255}
#define COR_TEXTO       (Color){232, 234, 240, 255}
#define COR_TEXTO2      (Color){107, 114, 128, 255}
#define COR_BORDA       (Color){ 55,  65,  81, 255}
#define COR_HOVER       (Color){ 36,  41,  61, 255}
#define COR_INPUT_ATIVO (Color){ 30,  58,  90, 255}

// ====== PRIMITIVOS DE UI ======
bool botao(const char* texto, int x, int y, int w, int h,
           Color corFundo, Color corTexto);
bool campoTexto(char* buffer, int maxLen, int x, int y, int w, int h,
                bool ativo, const char* placeholder);
void metricaCard(const char* label, const char* valor,
                 int x, int y, int w, int h, Color corValor);
void barraLateral(Sistema& s);
void mensagemSistema(Sistema& s);
void setMensagem(Sistema& s, const char* msg);

// ====== TELAS ======
void desenharMenu(Sistema& s);
void desenharCadastro(Sistema& s);
void desenharHistorico(Sistema& s);
void desenharBusca(Sistema& s);
void desenharPendentes(Sistema& s);

// ====== LOOP PRINCIPAL ======
Sistema iniciarSistema();
void desenharInterface(Sistema& s);

#endif // INTERFACE_H
