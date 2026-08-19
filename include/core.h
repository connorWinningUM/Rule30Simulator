#pragma once
#include "raylib.h"
#include <cstddef>
#include <vector>
#include <optional>

namespace simulation {
    const int MAX_SIM_DEPTH = 960;
    inline int simDepth = 200;
    class simulator {
        public:
            simulator() {
                grid.push_back(std::vector<bool>{true});
            };

            std::optional<std::vector<bool>> step();
            const std::vector<std::vector<bool>>& getGrid() const;

        
        private:
            std::vector<std::vector<bool>> grid;

            bool evalRule(bool p, bool q, bool r);
    };
}