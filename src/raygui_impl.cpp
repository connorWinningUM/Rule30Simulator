/*
* 
*    Purpose: Handles the compilation of raygui
* 
*/

#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <styles/style_jungle.h>
namespace render {
    void loadJungleTheme() {
        GuiLoadStyleJungle();
    }
}