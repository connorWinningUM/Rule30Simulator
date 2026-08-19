#pragma once
#include <raylib.h>
#include <vector>
#include <raygui.h>
#include <core.h>

namespace render {
    struct windowParameters {
        int width;
        int height;
        int targetFPS;
        const char* title;
        bool isFullscreen;
    };

    struct renderParameters {
        Color primary;
        Color secondary;
        Color bg;
    };

    void createWindow(windowParameters params);
    void drawMain(renderParameters renderParams, const std::vector<std::vector<bool>>& mainGrid, const simulation::statistics& stats);

    inline float sliderValue = 0.0f;
    void loadJungleTheme();
    void initUI();
    void drawUI();
    void drawStatistics(Rectangle statsArea, const simulation::statistics& stats);

    void drawGrid(
        const std::vector<std::vector<bool>>& grid,
        renderParameters renderParams,
        Rectangle bounds
    );
}