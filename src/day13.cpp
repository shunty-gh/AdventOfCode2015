#include <map>
#include <queue>
#include <regex>
#include <stdexcept>
#include <vector>

#include "aocutil.h"

// eg: Alice would lose 57 happiness units by sitting next to Bob.
const std::string Pattern{R"((\w+) would (lose|gain) (\d+) happiness units by sitting next to (\w+)\.)"};
const std::regex re{Pattern};

struct DinerKey {
    std::string From, To;
};

bool operator<(const DinerKey& a, const DinerKey& b) { return a.From == b.From ? a.To < b.To : a.From < b.From; }

struct DinerToVisit {
    std::string DinerName;
    int HappinessPoints;
    std::vector<std::string> Seated;
};

std::pair<std::vector<std::string>, std::map<DinerKey, int>> load_diners() {
    auto lines = getInputLines(13, false);
    std::map<DinerKey, int> diners{};
    std::vector<std::string> dinerNamesTmp{};
    std::smatch sm;
    for (auto &&line : lines) {
        if (!std::regex_match(line, sm, re)) {
            throw std::invalid_argument("Error matching input line: " + line);
        }
        DinerKey key{sm[1], sm[4]};
        int hp = (sm[2] == "lose" ? -1 * std::stoi(sm[3]) : std::stoi(sm[3]));
        diners[key] = hp;
        dinerNamesTmp.push_back(sm[1]);
    }

    std::vector<std::string> dinerNames;
    std::unique_copy(dinerNamesTmp.begin(), dinerNamesTmp.end(), std::back_inserter(dinerNames));
    return std::make_pair(dinerNames, diners);
}

int get_optimal_happiness(std::vector<std::string> dinerNames, std::map<DinerKey, int> dinerHappiness) {
    // Start with diner 0. Seat everyone else next to them, add up points, seat everyone else next to them etc
    int dc = dinerNames.size();
    auto firstDiner = dinerNames[0];
    int happiest = 0;
    std::queue<DinerToVisit> tovisit{};
    tovisit.push(DinerToVisit{firstDiner, 0, std::vector<std::string>{firstDiner}});
    DinerToVisit current;
    while (!tovisit.empty()) {
        current = tovisit.front();
        tovisit.pop();

        for (int i = 0; i < dc; i++) {
            auto dn = dinerNames[i];
            // Can't sit next to ourself
            if (current.DinerName == dn) {
                continue;
            }

            // Can't sit next to someone already seated
            if (std::find(current.Seated.begin(), current.Seated.end(), dn) != current.Seated.end()) {
                continue;
            }

            DinerKey k1{current.DinerName, dn};
            DinerKey k2{dn, current.DinerName};
            int hp = dinerHappiness[k1] + dinerHappiness[k2];

            // Is this person the last person to be seated
            if ((current.Seated.size() + 1) == dc) {
                // Also add the points for seating them next to the first person
                DinerKey kk1{dn, firstDiner};
                DinerKey kk2{firstDiner, dn};
                hp += (dinerHappiness[kk1] + dinerHappiness[kk2]);

                // Is this our best yet?
                if ((current.HappinessPoints + hp) > happiest) {
                    happiest = current.HappinessPoints + hp;
                }
                continue;
            }

            // ...otherwise, add to the seated list and add to the queue
            std::vector<std::string> seated{current.Seated};
            seated.push_back(dn);
            tovisit.push(DinerToVisit{dn, current.HappinessPoints + hp, seated});
        }
    }

    return happiest;
}

aoc_result_t day13() {
    auto dd = load_diners();
    auto dinerNames = dd.first;
    auto dinerHappiness = dd.second;

    int p1 = get_optimal_happiness(dinerNames, dinerHappiness);

    for (size_t i = 0; i < dinerNames.size(); i++) {
        dinerHappiness[DinerKey{"Me", dinerNames[i]}] = 0;
        dinerHappiness[DinerKey{dinerNames[i], "Me"}] = 0;
    }
    dinerNames.push_back("Me");

    int p2 = get_optimal_happiness(dinerNames, dinerHappiness);
    return {p1, p2};
}

