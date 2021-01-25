#include "aocutil.h"

const int TargetRow = 3010;
const int TargetCol = 3019;

const int Mult = 252533;
const int Mod = 33554393;
const long long int Start = 20151125;

aoc_result_t day25()
{
    /*
    Given a grid of the form
        |  1   2   3   4   5   6
    ---+---+---+---+---+---+---+
    1 |  1   3   6  10  15  21
    2 |  2   5   9  14  20
    3 |  4   8  13  19
    4 |  7  12  18
    5 | 11  17
    6 | 16

    The  1-based index of element in grid is (n^2 + n)/2 - (r - 1) where n = r + c - 1
    */
    int n = (TargetRow + TargetCol - 1);
    long int targetIndex = ((n * n) + n) / 2 - (TargetRow - 1);

    long long int code = Start;
    for (long int i = 2; i <= targetIndex; i++) {
        code = (code * Mult) % Mod;
    }
    return {code, "All Complete!"};
}
