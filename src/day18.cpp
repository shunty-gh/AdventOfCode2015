#include <functional>
#include <map>
#include <string>
#include "aoc2015.h"

struct Loc {
    int X, Y;
};
bool operator<(const Loc& a, const Loc& b) { return a.X == b.X ? a.Y < b.Y : a.X < b.X; }

struct State {
    bool Current, Next;
    State() { Current = false; Next = false; }
    State(bool current) { Current = current, Next = false; }
    State(bool current, bool next) { Current = current, Next = next; }
};

void prepare(std::map<Loc, State>&, bool);
void update(std::map<Loc, State>&);

aoc_result_t day18() {
    std::map<Loc, State> grid;
    int y = 0;
    getInputLines(18, false, [&grid, &y](std::string line) {
        for (int x = 0; x < (int)line.length(); x++) {
            grid[Loc{x,y}] = State{line[x] == '#'};
        }
        y++;
    });

    std::map<Loc, State> grid1{grid};
    for (int i = 0; i < 100; i++) {
        prepare(grid1, false);
        update(grid1);
    }

    int part1 = 0;
    for (auto&& [loc, cell] : grid1) {
        if (cell.Current) part1++;
    }

    std::map<Loc, State> grid2{grid};
    grid2[Loc{0,0}] = State{true, true};
    grid2[Loc{99,99}] = State{true, true};
    grid2[Loc{0,99}] = State{true, true};
    grid2[Loc{99,0}] = State{true, true};
    for (int i = 0; i < 100; i++) {
        prepare(grid2, true);
        update(grid2);
    }

    int part2 = 0;
    for (auto&& [loc, cell] : grid2) {
        if (cell.Current) part2++;
    }

    return {part1,part2};
}

const std::vector<Loc> Neighbours{Loc{1,0}, Loc{1,1}, Loc{0,1}, Loc{-1,1}, Loc{-1,0}, Loc{-1,-1}, Loc{0,-1}, Loc{1,-1}};

int get_active_neighbours(std::map<Loc, State>& grid, int x, int y) {
    int result = 0;
    for (auto& [dx, dy] : Neighbours) {
        int nextx = x + dx, nexty = y + dy;
        if (nextx < 0 || nexty < 0 || nextx >= 100 || nexty >= 100) {
            continue;
        }
        result += grid[Loc{nextx, nexty}].Current == true;
    }
    return result;
}

void prepare(std::map<Loc, State>& grid, bool part2) {
    int maxX = 100, maxY = 100;

    for (int y = 0; y < maxY; y++) {
        for (int x = 0; x < maxX; x++) {
            if (part2
                && ((x == 0 && y == 0) || (x == 99 && y == 99) || (x == 0 && y == 99 ) || (y == 0 && x == 99))) {
                continue;
            }

            int neighbours = get_active_neighbours(grid, x, y);

            Loc loc{x,y};
            State& current = grid[loc];
            if (current.Current) {
                grid[loc].Next = neighbours == 2 || neighbours == 3;
            } else {
                grid[loc].Next = neighbours == 3;
            }
        }
    }
}

void update(std::map<Loc, State>& grid) {
    for (auto&& [loc, cell] : grid) {
        cell.Current = cell.Next;
    }
}