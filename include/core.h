#pragma once
#include "raylib.h"
#include <cstddef>
#include <vector>
#include <optional>

namespace simulation {
    inline int simDepth = 200;

    struct statistics {
        float totalSimTime = 0.0f;
        float renderTime = 0.0f;
        float avgRowTime = 0.0f;
        size_t numRuleChecks = 0;
    };
    class simulator {
        public:
            simulator() {
                grid.push_back(std::vector<bool>{true});
            };

            std::optional<std::vector<bool>> step();
            void run();

            const std::vector<std::vector<bool>>& getGrid() const;
            const statistics& getStatistics() const;
            void setStatistics(const statistics& m_stats);
        
        private:
            std::vector<std::vector<bool>> grid;
            statistics stats;

            bool evalRule(bool p, bool q, bool r);
    };
}