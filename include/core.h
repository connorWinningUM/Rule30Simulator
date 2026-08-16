#pragma once
#include <vector>
#include <optional>

class simulation {
    public:
        simulation(int depth=0) : depth(depth) {
            grid.push_back(std::vector<bool>{true});
        };

        std::optional<std::vector<bool>> step();
        const std::vector<std::vector<bool>>& getGrid() const;

    
    private:
        int depth;
        std::vector<std::vector<bool>> grid;

        bool evalRule(bool p, bool q, bool r);
};