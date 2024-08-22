#include "raylib.h"

const Color myWhite = { 255, 255, 255, 255 };

int main() {
    // 初始化窗口
    InitWindow(800, 600, "Pixel Art Example");

    // 加载像素艺术图像
    Texture2D texture = LoadTexture("pixel_art.png");

    // 设置纹理滤镜为点过滤（保持像素清晰）
    SetTextureFilter(texture, 0);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(myWhite);

        // 绘制像素艺术图像
        DrawTexture(texture, 0, 0, myWhite);

        EndDrawing();
    }

    // 卸载图像
    UnloadTexture(texture);

    CloseWindow();

    return 0;
}
