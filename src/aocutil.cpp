#include <algorithm>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include "aoc2015.h"

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
