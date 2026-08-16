#pragma once
#include <raylib.h>
#include <vector>

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
    void drawGrid(
        const std::vector<std::vector<bool>>& grid, 
        Color primary,
        Color secondary
    );
}