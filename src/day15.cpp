#include <regex>
#include <string>
#include <vector>
#include "aoc2015.h"

const std::string Pattern{R"((\w+): capacity (-?\d+), durability (-?\d+), flavor (-?\d+), texture (-?\d+), calories (\d+).*)"};
const std::regex re{Pattern};

struct Ingredient {
    std::string Name;
    int Capcity, Durability, Flavour, Texture, Calories;
};

const int Teaspoons = 100;
const int TargetCalories = 500;

aoc_result_t day15() {

    std::vector<Ingredient> ingredients{};
    getInputLines(15, false, [&ingredients](std::string line) {
        std::smatch sm;
        std::regex_match(line, sm, re);
        ingredients.push_back(Ingredient{ sm[1], std::stoi(sm[2]), std::stoi(sm[3]), std::stoi(sm[4]), std::stoi(sm[5]), std::stoi(sm[6])});
    });

    uint64_t bestCookie = 0, best500 = 0, thiscookie = 0;
    int cap, dur, fla, tex, cal;
    // We know that there are 4 ingredients so we can limit the number of for... loops
    for (int i = 0; i <= Teaspoons; i++) {
        for (int j = 0; j <= Teaspoons && i + j <= Teaspoons; j++) {
            for (int k = 0; k <= Teaspoons && i + j + k <= Teaspoons; k++) {
                int l = Teaspoons - i - j - k;

                // Calculate cookie properties
                cap = (i * ingredients[0].Capcity) + (j * ingredients[1].Capcity) + (k * ingredients[2].Capcity) + (l * ingredients[3].Capcity);
                dur = (i * ingredients[0].Durability) + (j * ingredients[1].Durability) + (k * ingredients[2].Durability) + (l * ingredients[3].Durability);
                fla = (i * ingredients[0].Flavour) + (j * ingredients[1].Flavour) + (k * ingredients[2].Flavour) + (l * ingredients[3].Flavour);
                tex = (i * ingredients[0].Texture) + (j * ingredients[1].Texture) + (k * ingredients[2].Texture) + (l * ingredients[3].Texture);
                cal = (i * ingredients[0].Calories) + (j * ingredients[1].Calories) + (k * ingredients[2].Calories) + (l * ingredients[3].Calories);

                // Calculate cookie score
                thiscookie = (cap > 0 ? cap : 0)
                    * (dur > 0 ? dur : 0)
                    * (fla > 0 ? fla : 0)
                    * (tex > 0 ? tex : 0);

                // Part 1
                if (thiscookie > bestCookie) {
                    bestCookie = thiscookie;
                }
                // Part 2
                if (cal == TargetCalories && thiscookie > best500) {
                    best500 = thiscookie;
                }
            }
        }
    }
    return {bestCookie, best500};
}
