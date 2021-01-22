#include <algorithm>
#include <limits>
#include <map>
#include <queue>
#include <random>
#include <regex>
#include "aocutil.h"

const std::string MainPattern{R"((\w+) => (\w+))"};
const std::regex re_main{MainPattern};

struct Transform {
    std::string From, To;
};

struct ToTry {
    std::string Molecule;
    int Steps;
};

aoc_result_t day19()
{
    bool readfirst = true;
    std::string target_molecule;
    std::vector<Transform> transforms{};
    std::smatch sm;
    get_input_lines(19, false, [&](std::string line) {
        // Lines look like: Al => ThF
        if (line.length() == 0) {
            readfirst = false;
        } else if (readfirst) {
            std::regex_match(line, sm, re_main);
            transforms.push_back(Transform{sm[1], sm[2]});
        } else {
            target_molecule = line;
        }
    });

    // Part 1
    std::vector<std::string> replaced{};
    int mlen = target_molecule.length();
    for (const auto& [from, to] : transforms) {
        int fpos = 0;
        while (fpos >= 0 && fpos < mlen) {
            fpos = target_molecule.find(from, fpos);
            if (fpos >= 0) {
                std::string next{target_molecule};
                next.replace(fpos, from.length(), to);
                replaced.push_back(next);
                fpos++;
            }
        }
    }
    std::vector<std::string> replaced_distinct;
    std::sort(replaced.begin(), replaced.end());
    std::unique_copy(replaced.begin(), replaced.end(), std::back_inserter(replaced_distinct));
    int part1 = replaced_distinct.size();

    // Part 2
    // With sooo much help from
    // https://www.reddit.com/r/adventofcode/comments/3xflz8/day_19_solutions
    // Reverse the target string and continually apply the transforms in reverse.
    // Oddly enough if we just randomize the transform order and continually throw them
    // at the problem string it *very* quickly works itself out.
    int steps = 0;
    bool done = false;
    std::reverse(target_molecule.begin(), target_molecule.end());

    // Reverse the transform strings
    for (auto &&[from, to] : transforms) {
        std::reverse(to.begin(), to.end());
        if (from.length() > 1) {
            std::reverse(from.begin(), from.end());
        }
    }

    while (!done) {
        steps = 0;

        // Try a new arrangement of the transforms
        std::shuffle(transforms.begin(), transforms.end(), std::default_random_engine());

        std::string mol{target_molecule};
        while (mol != "e") {
            std::string molchk{mol};

            for (auto [to, from] : transforms) {
                int fpos = mol.find(from, 0);
                if (fpos >= 0) {
                    mol.replace(fpos, from.length(), to);
                    steps++;
                    if (mol == "e") {
                        done = true;
                        break;
                    }
                }
            }
            if (mol == molchk) {
                // No change. Need a new configuration of transforms
                break;
            }
        }
    }

    return {part1,steps};
}

