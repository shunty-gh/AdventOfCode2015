#include <algorithm>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include "aocutil.h"

/** Read input file for day number and apply a lambda to each line */
void getInputLines(int dayNumber, bool test, const std::function<void (std::string)>& processLine) {
    std::string dn = std::to_string(dayNumber);
    dn = std::string(2 - dn.length(), '0') + dn;
    std::string fn = "./input/day" + dn + (test ?  "-input-test.txt" : "-input.txt");

    std::fstream inputFile(fn, std::ios_base::in | std::ios_base::binary);
    std::string line;
    while (std::getline(inputFile, line)) {
        // Strip CR
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());

        processLine(line);
    }
}

/** Read input file for day number and return a vector of strings */
std::vector<std::string> getInputLines(int dayNumber, bool test = false) {
    std::vector<std::string> result;
    getInputLines(dayNumber, test, [&result](std::string line) { result.push_back(line); });
    return result;
}

std::vector<int> getInputInts(int dayNumber, bool test) {
    std::vector<int> result;
    getInputLines(dayNumber, test, [&result](std::string line) { result.push_back(std::stoi(line)); });
    return result;
}

std::vector<int> factorsOf(int num, bool sort) {
    std::vector<int> result{1, num};

    int ub = num / 2;
    int i = 2;
    while (i < ub) {
        if (num % i == 0) {
            ub = num / i;
            result.push_back(i);
            if (ub != i) result.push_back(ub);
        }
        i++;
    }

    if (sort) {
        std::sort(result.begin(), result.end());
    }
    return result;
}

std::pair<int, std::vector<int>> factorsOfAndSum(int num, bool sort) {
    int sum = 1 + num;
    std::vector<int> factors{1, num};

    int ub = num / 2;
    int i = 2;
    while (i < ub) {
        if (num % i == 0) {
            ub = num / i;
            factors.push_back(i);
            if (ub != i) factors.push_back(ub);
            sum += (i + ub);
        }
        i++;
    }

    if (sort) {
        std::sort(factors.begin(), factors.end());
    }
    return std::make_pair(sum, factors);
}

std::pair<int, std::vector<int>> factorsOfAndSum(int num) { return factorsOfAndSum(num, false); }
