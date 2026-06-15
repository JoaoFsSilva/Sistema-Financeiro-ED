#include "raylib.h"
#include "config.h"
#include "ui/interface.h"

int main() {
    InitWindow(LARGURA_TELA, ALTURA_TELA, TITULO_JANELA);
    SetTargetFPS(FPS_ALVO);

    Sistema s = iniciarSistema();

    while (!WindowShouldClose()) {
        BeginDrawing();
            desenharInterface(s);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
