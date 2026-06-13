#ifndef CONFIG_H
#define CONFIG_H

constexpr int         LARGURA_TELA  = 1280;
constexpr int         ALTURA_TELA   = 720;
constexpr int         FPS_ALVO      = 60;
constexpr const char* TITULO_JANELA = "Financas Pessoais";

constexpr int MAX_DESPESAS  = 500;
constexpr int MAX_HISTORICO = 100;
constexpr int MAX_PENDENTES = 500;
constexpr int MAX_DESC      = 128;
constexpr int MAX_CATEG     = 32;
constexpr int MAX_DATA      = 11;   // "DD/MM/AAAA" + '\0'

constexpr int         NUM_CATEGORIAS = 6;
constexpr const char* CATEGORIAS[NUM_CATEGORIAS] = {
    "Alimentacao", "Transporte", "Saude",
    "Lazer", "Moradia", "Outros"
};

enum Tela {
    TELA_MENU      = 0,
    TELA_CADASTRO  = 1,
    TELA_HISTORICO = 2,
    TELA_BUSCA     = 3,
    TELA_RELATORIO = 4,
    TELA_PENDENTES = 5
};

#endif // CONFIG_H
