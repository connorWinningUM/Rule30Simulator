#include "core.h"
#include <optional>
#include <vector>
#include <ranges>

//for (auto [left, center, right] : grid[step] | std::views::adjacent<3>)

std::optional<std::vector<bool>> simulation::simulator::step() {
    // grid[step] is the curr line
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

bool simulation::simulator::evalRule(bool p, bool q, bool r) {
    return p ^ (q | r);
}

const std::vector<std::vector<bool>>& simulation::simulator::getGrid() const {
    return grid;
}