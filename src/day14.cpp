#include <algorithm>
#include <regex>
#include <string>
#include <vector>
#include "aocutil.h"

const std::string pattern{R"((\w+) can fly (\d+) km/s for (\d+).* must rest for (\d+) seconds.)"};
const std::regex re{pattern};
const int Target_Time = 2503;

struct Rule {
    int Speed, Duration, Rest;
};

int get_distance(int, Rule);

aoc_result_t day14()
{
    std::vector<Rule> rules{};
    get_input_lines(14, false, [&](std::string line) {
        std::smatch sm;
        std::regex_match(line, sm, re);
        rules.push_back(Rule{std::stoi(sm[2]), std::stoi(sm[3]), std::stoi(sm[4])});
    });
    int rsz = rules.size();

    // Part 1
    int part1 = 0;
    for (auto& rule : rules) {
        int dist = get_distance(Target_Time, rule);
        if (dist > part1) {
            part1 = dist;
        }
    }

    // Part 2
    std::vector<int> points(rsz, 0);
    for (int t = 1; t <= Target_Time; t++) {
        int furthest = 0;
        int furthestIndex = 0;
        for (int r = 0; r < rsz; r++) {
            Rule rule = rules[r];
            int dist = get_distance(t, rule);
            if (dist > furthest) {
                furthest = dist;
                furthestIndex = r;
            }
        }
        points[furthestIndex] += 1;
    }
    int part2 = *std::max_element(points.begin(), points.end());

    return {part1, part2};
}

int get_distance(int time, Rule rule)
{
    int mod = rule.Duration + rule.Rest;
    auto dv = std::div(time, mod);
    int result = dv.quot * rule.Speed * rule.Duration;
    if (dv.rem >= rule.Duration) {
        result += rule.Speed * rule.Duration;
    } else {
        result += rule.Speed * dv.rem;
    }
    return result;
}