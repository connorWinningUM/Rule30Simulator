#include "core.h"
#include <optional>
#include <vector>
#include <ranges>
#include <chrono>

std::optional<std::vector<bool>> simulation::simulator::step() {
    if( grid.size() >= simulation::simDepth )
        return std::nullopt;

    std::vector<bool> newLine(grid.back().size()+2, false);
    if( grid.back().size() < 3 ) {
        newLine[0] = evalRule(false, false, grid.back()[0]);
        newLine[1] = evalRule(false, grid.back()[0], false);
        newLine[2] = evalRule(grid.back()[0], false, false);
        grid.push_back(newLine);
        return newLine;
    }

    //evaluate the first 2 padded 0's
    newLine[0] = evalRule(false, false, grid.back()[0]);
    newLine[1] = evalRule(false, grid.back()[0], grid.back()[1]);

    // core loop
    int count = 2;
    for (auto [left, center, right] : grid.back() | std::views::adjacent<3>) {
        newLine[count] = evalRule(left, center, right);
        count++;
    }

    //evaluate the last 2 padded 0's
    newLine[count] = evalRule( *(grid.back().end()-2), grid.back().back(), false);
    newLine[count+1] = evalRule( grid.back().back(), false, false);

    grid.push_back(newLine);
    return newLine;
}

void simulation::simulator::run() {
    grid = {{true}};
    stats.numRuleChecks = 0;

    auto start_time = std::chrono::high_resolution_clock::now();
    while(step()) {};
    auto end_time = std::chrono::high_resolution_clock::now();

    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(start_time).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time).time_since_epoch().count();
    stats.totalSimTime = (end - start) * 0.001;
    stats.avgRowTime = stats.totalSimTime / grid.size();
}

bool simulation::simulator::evalRule(bool p, bool q, bool r) {
    stats.numRuleChecks++;
    return p ^ (q | r);
}

const std::vector<std::vector<bool>>& simulation::simulator::getGrid() const {
    return grid;
}

const simulation::statistics& simulation::simulator::getStatistics() const {
    return stats;
}

void simulation::simulator::setStatistics(const statistics& m_stats) {
    stats = m_stats;
}