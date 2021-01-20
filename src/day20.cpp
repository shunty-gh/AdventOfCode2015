#include "aocutil.h"

const int Target = 36'000'000;
const int TargetBy10 = Target / 10;
const int TargetBy11 = Target / 11;

aoc_result_t day20() {
    int part1 = 0, part2 = 0;

    // Part 1
    std::vector<int> houses(TargetBy10 + 1, 0);

    for (int elf = 1; elf <= TargetBy10; elf++) {
        for (int house = elf; house <= TargetBy10; house += elf) {
            houses[house] += elf;
        }
    }
    for (int i = 1; i <= TargetBy10; i++) {
        if (houses[i] >= TargetBy10) {
            part1 = i;
            break;
        }
    }

    // Part 2
    std::vector<int> houses2(TargetBy11 + 1, 0);

    for (int elf = 1; elf <= TargetBy11; elf++) {
        int visited = 0;
        for (int house = elf; house <= TargetBy11 && visited < 50; house += elf, visited++) {
            houses2[house] += elf;
        }
    }
    for (int i = 1; i <= TargetBy11; i++) {
        if (houses2[i] >= TargetBy11) {
            part2 = i;
            break;
        }
    }

    return {part1, part2};
}
