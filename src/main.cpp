#include "raylib.h"
#include "config.h"

int main()
{
    InitWindow(LARGURA_TELA, ALTURA_TELA, TITULO_JANELA);
    SetTargetFPS(FPS_ALVO);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Financas Pessoais - em desenvolvimento", 40, 40, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
