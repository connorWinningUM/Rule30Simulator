#include "raylib.h"
#include <format>
#include <print>
#include <rendering.h>
#include <core.h>
#include <styles/style_jungle.h>
#include <chrono>

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

void render::drawMain(const std::vector<std::vector<bool>>& mainGrid, simulation::statistics& stats) {
    Rectangle gridArea;
    int margin = 100;
    gridArea.width = GetScreenWidth();
    gridArea.height = GetScreenHeight() - (margin);
    gridArea.x = 0;
    gridArea.y = margin;

    auto start_time = std::chrono::high_resolution_clock::now();
    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
    render::drawGrid(mainGrid, gridArea);
    render::drawUI();

    Rectangle statsArea(GetScreenWidth() - 230, GetScreenHeight()/2.0, 220, 200);
    render::drawStatistics(statsArea, stats);
    EndDrawing();
    auto end_time = std::chrono::high_resolution_clock::now();

    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(start_time).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time).time_since_epoch().count();
    stats.renderTime = (end - start) * 0.001;
}

void render::drawUI() {
    Rectangle transform;
    transform.x = 10;
    transform.y = 10;
    transform.height = GetScreenHeight() / 12.0f;
    transform.width = GetScreenWidth() - (2*transform.x);
    int bottomMargin = 20;
    int labelBottomMargin = 15;

    GuiLine(Rectangle(transform.x, transform.y + transform.height, transform.width, 1), "Settings");
    GuiSpinner(
        Rectangle(transform.x, transform.y, transform.width/20, transform.height - bottomMargin),
        "",
        &simulation::simDepth,
        0,
        9999,
        true
    );
    GuiLabel(Rectangle(transform.x + 12, transform.y + transform.height - labelBottomMargin, transform.width/20, 10), "Sim Depth");


}

void render::drawGrid( const std::vector<std::vector<bool>>& grid, Rectangle bounds ) {
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
            Color cellColor = val ? GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_PRESSED)) : Color(0);
            DrawRectangleRec(cell, cellColor);
            
            cell.x += cell.width;
        }

        cell.y += cell.height;
    }
}

void render::drawStatistics(Rectangle statsArea, const simulation::statistics& stats) {
    DrawRectangleRec(statsArea, Color(0, 0, 0, 124));
    int margin = 10;
    int labelHeight = 30;
    GuiLabel(
        Rectangle(statsArea.x+margin, statsArea.y+margin, statsArea.width-(2*margin), labelHeight),
        std::format("Total Sim Time: {:.4f}ms", stats.totalSimTime).c_str()
    );
    GuiLabel(
        Rectangle(statsArea.x+margin, statsArea.y+margin+labelHeight, statsArea.width-(2*margin), labelHeight),
        std::format("Average Row Sim Time: {:.4f}ms", stats.avgRowTime).c_str()
    );
    GuiLabel(
        Rectangle(statsArea.x+margin, statsArea.y+margin+2*labelHeight, statsArea.width-(2*margin), labelHeight),
        std::format("Num Of Rule Checks: {}", stats.numRuleChecks).c_str()
    );
    GuiLabel(
        Rectangle(statsArea.x+margin, statsArea.y+margin+3*labelHeight, statsArea.width-(2*margin), labelHeight),
        std::format("Render Time: {}", stats.renderTime).c_str()
    );
}
