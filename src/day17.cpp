#include <queue>
#include <string>
#include <vector>
#include "aocutil.h"

struct ContainerToTry {
    int Id, CurrentTotal;
    std::vector<int> Contents;
};

const int TargetSize = 150;

aoc_result_t day17() {
    std::vector<int> input = get_input_ints(17, false);

    std::vector<std::vector<int>> combinations{};
    int isize = input.size();
    int part1 = 0;
    int shortest = isize;
    for (int i = 0; i < isize; i++) {
        std::queue<ContainerToTry> tovisit{};
        tovisit.push(ContainerToTry{i, input[i], std::vector<int>{i}});
        ContainerToTry current;
        while (!tovisit.empty()) {
            current = tovisit.front();
            tovisit.pop();

            for (int j = current.Id + 1; j < isize; j++) {
                int newtot = current.CurrentTotal + input[j];
                if (newtot >= TargetSize) {
                    if (newtot == TargetSize) {
                        std::vector<int> vec{current.Contents};
                        vec.push_back(j);
                        if ((int)vec.size() <= shortest) {
                            shortest = (int)vec.size();
                            combinations.push_back(vec);
                        }
                        part1++;
                    }
                    continue;
                }

                std::vector<int> newcont{current.Contents};
                newcont.push_back(j);
                tovisit.push(ContainerToTry{j, newtot, newcont});
            }
        }
    }
    int part2 = 0;
    for (auto &&comb : combinations) {
        if (shortest == (int)comb.size()) {
            part2++;
        }
    }

    return {part1,part2};
}