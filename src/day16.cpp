#include <regex>
#include <string>
#include <vector>
#include "aocutil.h"

// eg: Sue 27: cars: 0, trees: 8, akitas: 5
const std::string Pattern{R"(\w+ (\d+): (\w+): (\d+), (\w+): (\d+), (\w+): (\d+).*)"};
const std::regex re{Pattern};

enum class Compound {
    children,
    cats,
    samoyeds,
    pomeranians,
    akitas,
    vizslas,
    goldfish,
    trees,
    cars,
    perfumes,
    unknown,
};

Compound str_to_compound(std::string source) {
    if (source == "children") return Compound::children;
    if (source == "cats") return Compound::cats;
    if (source == "samoyeds") return Compound::samoyeds;
    if (source == "pomeranians") return Compound::pomeranians;
    if (source == "akitas") return Compound::akitas;
    if (source == "vizslas") return Compound::vizslas;
    if (source == "goldfish") return Compound::goldfish;
    if (source == "trees") return Compound::trees;
    if (source == "cars") return Compound::cars;
    if (source == "perfumes") return Compound::perfumes;
    return Compound::unknown;
}

struct Aunt {
    int Id;
    std::vector<int> Compounds;
    bool Potential;

    Aunt(int id) { Id = id; Compounds = std::vector<int>(11, -1); Potential = true; }
};

const std::vector<int> CompoundsFound {3, 7, 2, 3, 0, 0, 5, 3, 2, 1};

aoc_result_t day16() {
    std::vector<Aunt> aunts;
    getInputLines(16, false, [&aunts](std::string line) {
        std::smatch sm;
        std::regex_match(line, sm, re);
        std::vector<int>(11, -1);

        Aunt aunt{ std::stoi(sm[1]) };
        Compound c1 = str_to_compound(sm[2]);
        int v1 = std::stoi(sm[3]);
        Compound c2 = str_to_compound(sm[4]);
        int v2 = std::stoi(sm[5]);
        Compound c3 = str_to_compound(sm[6]);
        int v3 = std::stoi(sm[7]);
        aunt.Compounds[(int)c1] = v1;
        aunt.Compounds[(int)c2] = v2;
        aunt.Compounds[(int)c3] = v3;
        aunts.push_back(aunt);
    });

    // To find which aunt it *is* we need to filter out which aunts it
    // definitely *isn't* by determining if each aunt has the required
    // number of items.

    // Part 1
    for (size_t i = 0; i < CompoundsFound.size(); i++) {
        int ccount = CompoundsFound[i];
        for (auto &&aunt : aunts) {
            if (aunt.Compounds[i] > 0 && aunt.Compounds[i] != ccount) {
                // can't be this aunt because they definitely don't have the correct number of this item
                aunt.Potential = false;
            }
        }
    }

    // find the "potential"s - should be only 1
    int auntid1 = 0;
    for (auto &&aunt : aunts) {
        if (aunt.Potential) {
            auntid1 = aunt.Id;
        }
    }

    // Reset for part 2
    for (auto &&aunt : aunts) {
        aunt.Potential = true;
    }

    // Part 2
    // cats & trees => greater than
    // pomeranians & goldfish => less than
    for (size_t i = 0; i < CompoundsFound.size(); i++) {
        int ccount = CompoundsFound[i];
        bool gt = (i == (int)Compound::cats) || (i == (int)Compound::trees);
        bool lt = (i == (int)Compound::pomeranians) || (i == (int)Compound::goldfish);

        for (auto &&aunt : aunts) {
            if (aunt.Compounds[i] == -1) continue; // no further info

            int ac = aunt.Compounds[i];
            if (gt) {
                if (ac <= ccount) {
                    aunt.Potential = false;
                }
            }  else if (lt) {
                if (ac >= ccount) {
                    aunt.Potential = false;
                }
            } else {
                if (ac != ccount) {
                    aunt.Potential = false;
                }
            }
        }
    }

    // find the "potential"s - should be only 1
    int auntid2 = 0;
    for (auto &&aunt : aunts) {
        if (aunt.Potential) {
            auntid2 = aunt.Id;
        }
    }

    return {auntid1,auntid2};
}
