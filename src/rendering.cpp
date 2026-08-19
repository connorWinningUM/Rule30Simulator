#include "raylib.h"
#include <print>
#include <rendering.h>
#include <core.h>
#include <styles/style_jungle.h>

void render::initUI() {
    render::loadJungleTheme(); // Applies the Jungle palette cleanly
}

void render::createWindow(windowParameters params) {
    InitWindow(params.width, params.height, params.title);

    if( params.isFullscreen ) {
        SetConfigFlags(FLAG_WINDOW_UNDECORATED);
        int currentMonitor = GetCurrentMonitor();
        SetWindowPosition(
            GetMonitorPosition(currentMonitor).x,
            GetMonitorPosition(currentMonitor).y
        );
        SetWindowSize(
            GetMonitorWidth(currentMonitor),
            GetMonitorHeight(currentMonitor)
        );
    }
    SetTargetFPS(params.targetFPS);
}

void render::drawMain(render::renderParameters renderParams, const std::vector<std::vector<bool>>& mainGrid, const simulation::statistics& stats) {
    GuiLoadStyleJungle();
    
    Rectangle gridArea;
    int margin = 100;
    gridArea.width = GetScreenWidth();
    gridArea.height = GetScreenHeight() - (margin);
    gridArea.x = 0;
    gridArea.y = margin;

    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
    render::drawGrid(mainGrid, renderParams, gridArea);
    render::drawUI();

    Vector2 statsPos(GetScreenWidth() - 200, GetScreenHeight() - 400);
    render::drawStatistics(statsPos, stats);
    EndDrawing();
}

void render::drawUI() {
    Rectangle transform;
    transform.x = 10;
    transform.y = 10;
    transform.height = GetScreenHeight() / 12.0f;
    transform.width = GetScreenWidth() - (2*transform.x);
    int bottomMargin = 20;

    GuiLine(Rectangle(transform.x, transform.y + transform.height, transform.width, 1), "Settings");
    GuiSpinner(
        Rectangle(transform.x, transform.y, transform.width/20, transform.height - bottomMargin),
        "",
        &simulation::simDepth,
        0,
        9999,
        true
    );
}

void render::drawGrid( const std::vector<std::vector<bool>>& grid, render::renderParameters renderParams, Rectangle bounds ) {
    if (grid.empty()) return;

    Rectangle cell;
    cell.width = bounds.width / grid.back().size();
    cell.height = bounds.height / grid.size();
    cell.x = 0;
    cell.y = bounds.y;

    // determine appropiate mipmap size
    if( (cell.width > 0.5 || cell.height > 0.5) && (cell.width < 1 || cell.height < 1) ) {
        cell.width = 1;
        cell.height = 1;
    }

    for (const auto& row : grid) {
        int rowWidth = static_cast<int>(row.size());
        
        float center = bounds.x + (bounds.width / 2);
        cell.x = center - (rowWidth / 2.0 * cell.width);

        for (bool val : row) {
            Color cellColor = val ? renderParams.primary : Color(0);
            DrawRectangleRec(cell, cellColor);
            
            cell.x += cell.width;
        }

        cell.y += cell.height;
    }
}

void render::drawStatistics(Vector2 pos, const simulation::statistics& stats) {
    return;
}
