#include <raylib.h>
#include <core.h>
#include <rendering.h>
#include <cstdio>
#include <print>
#include <toml++/toml.hpp>
#include <configParsing.h>

int main() {

    toml::table config;
    try {
        config = toml::parse_file("config.toml");
    } catch (const toml::parse_error& err) {
        std::println(stderr, "Config Parsing Failed:\n{}" , err.what());
        return 1;
    }

    // retreives window params using value_or() which is passed the default value
    render::windowParameters windowParams = parseWindowParams(config);

    const int SELECTED_DEPTH = config["simulation"]["simDepth"].value_or(100);
    render::renderParameters renderParams = parseRenderParams(config);

    render::createWindow(windowParams);

    simulation sim(SELECTED_DEPTH);
    while(sim.step()) {};

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(renderParams.bg);
        render::drawGrid(sim.getGrid(), renderParams.primary, renderParams.secondary);
        EndDrawing();
    }

    CloseWindow();
}
