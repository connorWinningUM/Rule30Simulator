#pragma once
#include <rendering.h>
#include <toml++/toml.hpp>

render::windowParameters parseWindowParams(toml::table& config);

render::renderParameters parseRenderParams(toml::table& config);
