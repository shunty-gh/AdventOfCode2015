#include <iostream>
#include <string>
#include <vector>

#include "aoc2015.h"
#include "ezOptionParser.hpp"

static const std::vector<aoc_t> aocDays = {
    { day01 }, { day02 }, { day03 }, { day04 }, { day05 },
    { day06 }, { day07 }, { day08 }, { day09 }, { day10 },
    { day11 }, { day12 }, { day13 }, { day14 }, { day15 },
    { day16 }, { day17 }, { day18 }, { day19 }, { day20 },
    { day21 }, { day22 }, { day23 }, { day24 }, { day25 },
};

int main(int argc, const char* argv[]) {
    std::cout << "\n" << WHITE << BK_RED << " *** Advent of Code 2015 *** " << RESET << "\n\n";

    // Day params
    ez::ezOptionParser opt;
    opt.overview = "Advent of code 2015";
    opt.add(
        "",
        0,
        -1,
        ',',
        "Day numbers to include",
        "-d",
        "--days"
    );
    opt.parse(argc, argv);
    std::vector<int> daysToInclude{};
    opt.get("-d")->getInts(daysToInclude);
    if (daysToInclude.size() == 0) {
        for (int i = 1; i <= 25; i++) {
            daysToInclude.push_back(i);
        }
    }

    for (size_t di = 0; di < daysToInclude.size(); di++) {
        int day = daysToInclude[di];
        auto &dayFn = aocDays[day - 1];
        if (!dayFn.fn) continue;

        auto result = dayFn.fn();

        std::cout << BLUE << "Day " << day << RESET << "\n";
        std::cout << "  Part 1: " << YELLOW << result.answer[0] << RESET << "\n";
        std::cout << "  Part 2: " << YELLOW << result.answer[1] << RESET << "\n";
    }
}

aoc_result_t day02() { return {0,0}; }
aoc_result_t day03() { return {0,0}; }
aoc_result_t day04() { return {0,0}; }
aoc_result_t day05() { return {0,0}; }
aoc_result_t day06() { return {0,0}; }
aoc_result_t day07() { return {0,0}; }
aoc_result_t day08() { return {0,0}; }
aoc_result_t day09() { return {0,0}; }
aoc_result_t day10() { return {0,0}; }
aoc_result_t day11() { return {0,0}; }
aoc_result_t day12() { return {0,0}; }
aoc_result_t day14() { return {0,0}; }
aoc_result_t day17() { return {0,0}; }
aoc_result_t day18() { return {0,0}; }
aoc_result_t day19() { return {0,0}; }
aoc_result_t day20() { return {0,0}; }
aoc_result_t day21() { return {0,0}; }
aoc_result_t day22() { return {0,0}; }
aoc_result_t day23() { return {0,0}; }
aoc_result_t day24() { return {0,0}; }
aoc_result_t day25() { return {0,0}; }
