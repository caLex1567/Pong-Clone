#include "raylib.h"

int main(void) {
    InitWindow(800, 450, "pong-window");
    SetTargetFPS(60);

    Vector2 center = {400, 225};
    float radius = {15};
    Rectangle rect1 = {0, 195, 5, 60};
    Rectangle rect2 = {795, 195, 5, 60};
    float speedBar = 400.0;

    while (!WindowShouldClose()) {
        Vector2 dirBar1 = {IsKeyDown(KEY_D) - IsKeyDown(KEY_A),
                           IsKeyDown(KEY_S) - IsKeyDown(KEY_W)};
        Vector2 dirBar2 = {IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT),
                           IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP)};

        rect1.y += dirBar1.y * speedBar * GetFrameTime();
        rect2.y += dirBar2.y * speedBar * GetFrameTime();

        if (rect1.y < 0)
            rect1.y = 0;
        else if (rect1.y > 390)
            rect1.y = 390;
        if (rect2.y < 0)
            rect2.y = 0;
        else if (rect2.y > 390)
            rect2.y = 390;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(center, radius, RED);
        DrawRectangleRec(rect1, BLACK);
        DrawRectangleRec(rect2, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
