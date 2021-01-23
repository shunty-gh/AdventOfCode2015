#include <numeric>
#include <limits>
#include <queue>
#include <set>
#include "aocutil.h"

struct QueueItem {
    int Package;
    int PackageSum;
    long long int QE;
    std::vector<int> Packages;

    QueueItem() { Package = 0; PackageSum = 0; QE = 0; Packages = std::vector<int>{}; }
    QueueItem(int p) { Package = p; PackageSum = p; QE = p; Packages = std::vector<int>{p}; }
};


long long int distribute_packages(std::vector<int>&, int);

aoc_result_t day24()
{
    std::vector<int> packages = get_input_ints(24, false);
    auto part1 = distribute_packages(std::vector<int>{packages}, 3);
    auto part2 = distribute_packages(std::vector<int>{packages}, 4);
    return {part1, part2};
}

long long int distribute_packages(std::vector<int>& packages, int groupCount)
{
    int ps = std::accumulate(packages.begin(), packages.end(), 0);
    std::sort(packages.begin(), packages.end(), [](const int& a, const int& b) { return a > b; });
    int groupTarget = ps / groupCount;
    std::queue<QueueItem> q;
    for (auto& i : packages) {
        q.push(QueueItem{i});
    }

    int lowestCount = INT_MAX;
    long long lowestQE = LLONG_MAX;
    std::set<long long int> seen{};
    QueueItem current;
    bool done = false;
    while (!q.empty() && !done) {
        current = q.front();
        q.pop();

        // Find neighbours/next items
        for (auto &&i : packages) {
            if (std::find(current.Packages.begin(), current.Packages.end(), i) != current.Packages.end()) {
                continue;
            }
            if (current.PackageSum + i > groupTarget) {
                continue;
            }

            QueueItem qi{current};
            qi.Package = i;
            qi.PackageSum += i;
            qi.QE *= i;
            qi.Packages.push_back(i);

            int psize = current.Packages.size();
            if ((psize > lowestCount) || (psize == lowestCount && qi.QE >= lowestQE)) {
                continue;
            }

            if (qi.PackageSum == groupTarget) {
                if (lowestCount > psize) {
                    lowestCount = psize;
                    if (lowestQE > qi.QE) {
                        lowestQE = qi.QE;
                    }
                }

                continue;
            }
            if (seen.find(qi.QE) != seen.end()) {
                continue;
            }
            seen.emplace(qi.QE);
            q.push(qi);
        }
    }

    return lowestQE;
}