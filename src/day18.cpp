#include <functional>
#include <string>
#include <vector>
#include "aoc2015.h"

struct State {
    bool Current, Next;
    State() { Current = false; Next = false; }
    State(bool current) { Current = current, Next = false; }
    State(bool current, bool next) { Current = current, Next = next; }
};

/* Defining the grid as a vector<int> rather than a map<...> speeds up the
   process by about 6x. We just need to take care when working out the
   neighbours for indexes at the edges of the 'grid' - eg if current
   index = 100 then the neigbours are
   0, 1, 101, 200, 201 - ie NOT including 99, 199
 */

const int MaxIndex = 100 * 100;
const int TopLeft = 0;
const int TopRight = 99;
const int BottomLeft = (99 * 100);
const int BottomRight = (99 * 100) + 99;

void prepare(std::vector<State>&, bool);
void update(std::vector<State>&);

aoc_result_t day18() {
    std::vector<State> grid;
    getInputLines(18, false, [&grid](std::string line) {
        for (int x = 0; x < (int)line.length(); x++) {
            grid.push_back(State{line[x] == '#'});
        }
    });

    std::vector<State> grid1{grid};
    for (int i = 0; i < 100; i++) {
        prepare(grid1, false);
        update(grid1);
    }

    int part1 = 0;
    for (auto&& cell : grid1) {
        if (cell.Current) part1++;
    }

    std::vector<State> grid2{grid};
    grid2[TopLeft] = State{true, true};
    grid2[TopRight] = State{true, true};
    grid2[BottomLeft] = State{true, true};
    grid2[BottomRight] = State{true, true};
    for (int i = 0; i < 100; i++) {
        prepare(grid2, true);
        update(grid2);
    }

    int part2 = 0;
    for (auto&& cell : grid2) {
        if (cell.Current) part2++;
    }

    return {part1,part2};
}

std::vector<int> get_neighbours(int index) {
    int y = index / 100;
    int x = index % 100;

    // Preallocate makes it much quicker than .push_back()
    // all the time as we know max number we'll need and
    // it gets called a lot
    std::vector<int> result(8, -1);

    if (x > 0) result[0] = index - 1;
    if (x < 99) result[1] = index + 1;

    // Add elements from 'row' above
    if (y > 0) {
        if (x > 0) result[2] = index - 100 - 1;
        result[3] = index - 100;
        if (x < 99) result[4] = index - 100 + 1;
    }

    // Add elements from 'row' below
    if (y < 99) {
        if (x > 0) result[5] = index + 100 - 1;
        result[6] = index + 100;
        if (x < 99) result[7] = index + 100 + 1;
    }

    return result;
};

int get_active_neighbours(const std::vector<State>& grid, int index, int maxOfInterest) {
    int result = 0;
    for (auto& nexti : get_neighbours(index)) {
        if (nexti >= 0) {
            result += grid[nexti].Current == true;
            if (result >= maxOfInterest) { // No need to continue if we've got more than we need
                break;
            }
        }
    }
    return result;
}

void prepare(std::vector<State>& grid, bool part2) {
    for (int i = 0; i < MaxIndex; i++) {
        if (part2
            && (i == TopLeft || i == TopRight || i == BottomLeft || i == BottomRight)) {
            continue;
        }

        int neighbours = get_active_neighbours(grid, i, 4);

        if (grid[i].Current) {
            grid[i].Next = neighbours == 2 || neighbours == 3;
        } else {
            grid[i].Next = neighbours == 3;
        }
    }
}

void update(std::vector<State>& grid) {
    for (auto&& cell : grid) {
        cell.Current = cell.Next;
    }
}