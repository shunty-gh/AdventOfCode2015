#include "aocutil.h"

const int Target = 36'000'000;
const int TargetBy10 = Target / 10;
const int TargetBy11 = Target / 11;

aoc_result_t day20() {
    int part1 = 0, part2 = 0;
    for (int i = 1; part1 == 0 || part2 == 0 ; i++) {
        auto&& [sum, factors] = factorsOfAndSum(i);
        if (sum >= TargetBy10) {
            if (part1 == 0) {
                part1 = i;
            }

            if (part2 == 0 && (sum >= TargetBy11)) {
                // Need to sum without the elves that have stopped delivering
                int esum = 0;
                for (auto &&x: factors) {
                    if ((x * 50) < i) {
                        continue;
                    }
                    esum += x;
                }

                if (esum >= TargetBy11) {
                    part2 = i;
                }
            }
        }
    }

    return {part1, part2};
}
