#include <configParsing.h>
#include <rendering.h>
#include <toml++/toml.hpp>

render::windowParameters parseWindowParams(toml::table& config) {
    render::windowParameters windowParams;
    windowParams.height = config["window"]["height"].value_or(1080);
    windowParams.width = config["window"]["width"].value_or(1920);
    windowParams.title = config["window"]["title"].value_or("Rule30 Simulation");
    windowParams.isFullscreen = config["window"]["isFullscreen"].value_or(false);
    windowParams.targetFPS = config["window"]["targetFPS"].value_or(60);
    return windowParams;
}