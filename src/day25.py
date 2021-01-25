TARGET_ROW = 3010
TARGET_COL = 3019

MULT = 252533
MOD = 33554393
START = 20151125

# Given a grid of the form
#   |  1   2   3   4   5   6
#---+---+---+---+---+---+---+
# 1 |  1   3   6  10  15  21
# 2 |  2   5   9  14  20
# 3 |  4   8  13  19
# 4 |  7  12  18
# 5 | 11  17
# 6 | 16

# 1-based index of element in grid is (n^2 + n)/2 - (r - 1) where n = r + c - 1
n = (TARGET_ROW + TARGET_COL - 1)
targetIndex = (pow(n,2) + n) // 2 - (TARGET_ROW - 1)

code = START
for i in range(targetIndex - 1):
    code = (code * MULT) % MOD
print("Part 1: ", code)

# I reckon this is marginally easier to understand, but it's a teeny bit slower
# code = START
# rstart = 1
# part1 = 0
# while part1 == 0:
#     rstart += 1
#     for row in range(rstart, 0, -1):
#         code = (code * MULT) % MOD
#         if row == TARGET_ROW and (rstart - row + 1) == TARGET_COL:
#             part1 = code
#             break

# print("Part 1: ", part1)
