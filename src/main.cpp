#include <raylib.h>
#include <core.h>
#include <rendering.h>
#include <cstdio>
#include <print>
#include <toml++/toml.hpp>
#include <configParsing.h>
#include <styles/style_jungle.h>

int main() {

    toml::table config;
    try {
        config = toml::parse_file("config.toml");
    } catch (const toml::parse_error& err) {
        std::println(stderr, "Config Parsing Failed:\n{}" , err.what());
        return 1;
    }
    render::windowParameters windowParams = parseWindowParams(config);

    render::createWindow(windowParams);
    GuiLoadStyleJungle();

    simulation::simulator sim;
    sim.run();
    
    int prevSimDepth = simulation::simDepth;
    while(!WindowShouldClose()) {
        if(simulation::simDepth != prevSimDepth) {
            sim.run();
            prevSimDepth = simulation::simDepth;
        }

        simulation::statistics updatedStats(sim.getStatistics());
        render::drawMain( sim.getGrid(), updatedStats );
        sim.setStatistics(updatedStats);
    }

    CloseWindow();
}
