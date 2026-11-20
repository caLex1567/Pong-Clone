#include "raylib.h"

int main(void) {
    InitWindow(800, 450, "pong-window");
    SetTargetFPS(60);

    Vector2 center = {400, 225};
    float radius = {15};
    Rectangle rect1 = {0, 195, 5, 60};
    Rectangle rect2 = {795, 195, 5, 60};
    float speedBar = 400.0;
    float speedCircle = 125.0;

    int xCircle = GetRandomValue(0, 1) ? 1 : -1;
    int yCircle = GetRandomValue(0, 1) ? 1 : -1;

    // Ball initial direction
    Vector2 dirCircle = {xCircle, yCircle};

    while (!WindowShouldClose()) {

        // update

        // Paddle controls
        Vector2 dirBar1 = {IsKeyDown(KEY_D) - IsKeyDown(KEY_A),
                           IsKeyDown(KEY_S) - IsKeyDown(KEY_W)};
        Vector2 dirBar2 = {IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT),
                           IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP)};

        // Ball movements
        center.x += dirCircle.x * speedCircle * GetFrameTime();
        center.y += dirCircle.y * speedCircle * GetFrameTime();

        // Ball upper and lower boundary collisions
        if (center.y <= radius || center.y >= 450 - radius)
            dirCircle.y *= -1;

        // Stage 1 of ball and paddle collision
        if (CheckCollisionCircleRec(center, radius, rect1) ||
            CheckCollisionCircleRec(center, radius, rect2)) {
            dirCircle.x *= -1;
            speedCircle *= 1.2;
        }
        // Game Over
        bool gameOver = (center.x - radius <= 0 || center.x + radius >= 800);

        // Paddle movements
        rect1.y += dirBar1.y * speedBar * GetFrameTime();
        rect2.y += dirBar2.y * speedBar * GetFrameTime();

        // Window boundaries
        if (rect1.y < 0)
            rect1.y = 0;
        else if (rect1.y > 390)
            rect1.y = 390;
        if (rect2.y < 0)
            rect2.y = 0;
        else if (rect2.y > 390)
            rect2.y = 390;

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(center, radius, RED);
        DrawRectangleRec(rect1, BLACK);
        DrawRectangleRec(rect2, BLACK);
        EndDrawing();
        while (gameOver) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            char *msg = "GAME OVER";
            int lenText = MeasureText(msg, 40);
            DrawText(msg, 400 - (lenText / 2), 225 - (40 / 2), 40, RED);
            EndDrawing();
            if (IsKeyPressed(KEY_R)) {
                center.x = 400;
                center.y = 225;
                speedCircle = 100.0;
                xCircle = GetRandomValue(0, 1) ? 1 : -1;
                yCircle = GetRandomValue(0, 1) ? 1 : -1;
                break;
            } else
                continue;
        }
    }
    CloseWindow();
    return 0;
}
