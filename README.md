# Rule30 Simulator
This project is a C++ application that simulates and visualizes Wolfram's Rule 30, a one-dimensional cellular automaton. The visualization is rendered using the Raylib library, and all simulation and rendering parameters are configurable through a TOML file.

## Features
-   Generates a Rule 30 cellular automaton pattern.
-   Renders the simulation grid graphically using Raylib.
-   Highly configurable via an external `config.toml` file.
-   Customizable window settings: dimensions, title, fullscreen mode, and target FPS.
-   Adjustable simulation depth.
-   Customizable colors for active cells, inactive cells, and the background.

## Configuration
The simulation's behavior and appearance can be modified by editing the `config.toml` file.

```toml
[window]
height = 1080
width = 1920
title = "Rule30 Simulation"
isFullscreen = true
targetFPS = 60

[simulation]
simDepth = 200

[render]
primaryColor = [ 3, 90, 252 ]
secondaryColor = [ 0, 0, 0]
bgColor = [0, 0, 0]
```
-   **`[window]`**: Controls the display window properties.
    -   `height`, `width`: The window dimensions in pixels.
    -   `title`: The text displayed in the window's title bar.
    -   `isFullscreen`: Set to `true` for fullscreen mode or `false` for windowed mode.
    -   `targetFPS`: The target frames per second for the rendering loop.
-   **`[simulation]`**: Controls the automaton's properties.
    -   `simDepth`: The number of generations (rows) to compute and display.
-   **`[render]`**: Defines the color scheme. Colors are specified as an array of RGB values `[R, G, B]`.
    -   `primaryColor`: The color of active (`true`) cells.
    -   `secondaryColor`: The color of inactive (`false`) cells.
    -   `bgColor`: The background color of the window.

## Dependencies
-   **CMake** (version 3.15 or higher)
-   A C++ compiler supporting **C++23**

The following libraries are automatically fetched by CMake during the build process using `FetchContent`:
-   [Raylib 5.0](https://github.com/raysan5/raylib)
-   [toml++ v3.4.0](https://github.com/marzer/tomlplusplus)

## Building and Running
You can build and run the project using the provided shell script or by executing the CMake commands manually.

### Using the script
Clone the repository, make the script executable, and run it:
```bash
git clone https://github.com/connorwinningum/Rule30Simulator.git
cd Rule30Simulator
chmod +x run.sh
./run.sh
```

### Manual Build
If you prefer to build the project manually, follow these steps:
```bash
# Clone the repository
git clone https://github.com/connorwinningum/Rule30Simulator.git
cd Rule30Simulator

# Configure the project with CMake
cmake -B build .

# Build the project
cmake --build build

# Run the executable
./build/Rule30