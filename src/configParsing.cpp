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

render::renderParameters parseRenderParams(toml::table& config) {
    render::renderParameters renderParams;
    
    Color primary(
        config["render"]["primaryColor"][0].value_or(0),
        config["render"]["primaryColor"][1].value_or(0),
        config["render"]["primaryColor"][2].value_or(0),
        255
    );
    renderParams.primary = primary;

    Color secondary( 
        config["render"]["secondaryColor"][0].value_or(0),
        config["render"]["secondaryColor"][1].value_or(0),
        config["render"]["secondaryColor"][2].value_or(0),
        255
    );
    renderParams.secondary = secondary;

    Color bgColor(
        config["render"]["bgColor"][0].value_or(0),
        config["render"]["bgColor"][1].value_or(0),
        config["render"]["bgColor"][2].value_or(0),
        255
    );
    renderParams.bg = bgColor;

    renderParams.primary = primary;
    renderParams.secondary = secondary;
    renderParams.bg = bgColor;
    return renderParams;
}