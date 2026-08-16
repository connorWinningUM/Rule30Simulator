#include "raylib.h"
#include <rendering.h>

void render::createWindow(windowParameters params) {
    SetTargetFPS(params.targetFPS);
    if( params.isFullscreen )
        SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(params.width, params.height, params.title);
}

void render::drawGrid(const std::vector<std::vector<bool>>& grid, Color primary, Color secondary) {
    if (grid.empty()) return;

    int cellSize = GetScreenWidth() / grid.back().size();
    int screenWidth = GetScreenWidth();
    int currentRowY = 0;

    for (const auto& row : grid) {
        int rowWidth = static_cast<int>(row.size());
        int totalRowWidthPixels = rowWidth * cellSize;
        
        int currentX = (screenWidth / 2) - (totalRowWidthPixels / 2);

        for (bool val : row) {
            Color cellColor = val ? primary : secondary;
            DrawRectangle(currentX, currentRowY, cellSize, cellSize, cellColor);
            
            currentX += cellSize;
        }

        currentRowY += cellSize;
    }
}
