#include <regex>
#include "aocutil.h"

const std::string Pattern{R"((\w{3}) ([a-z]|([+-]\d{1,2}))(, ([+-]\d{1,2}))?)"};
const std::regex re{Pattern};

enum class Opcode {
    error_undefined,
    hlf, // hlf r sets register r to half its current value, then continues with the next instruction.
    tpl, // tpl r sets register r to triple its current value, then continues with the next instruction.
    inc, // inc r increments register r, adding 1 to it, then continues with the next instruction.
    jmp, // jmp offset is a jump; it continues with the instruction offset away relative to itself.
    jie, // jie r, offset is like jmp, but only jumps if register r is even ("jump if even").
    jio, // jio r, offset is like jmp, but only jumps if register r is 1 ("jump if one", not odd).
};

struct Instruction {
    Opcode Opcode;
    char RegA, RegB;
    int ValA, ValB;
};

Opcode str_to_opcode(std::string opcode) {
    if (opcode == "hlf") return Opcode::hlf;
    if (opcode == "tpl") return Opcode::tpl;
    if (opcode == "inc") return Opcode::inc;
    if (opcode == "jmp") return Opcode::jmp;
    if (opcode == "jie") return Opcode::jie;
    if (opcode == "jio") return Opcode::jio;
    return Opcode::error_undefined;
}

int run_program(std::vector<Instruction>&, int);

aoc_result_t day23() {
    std::vector<Instruction> instructions{};
    getInputLines(23, false, [&instructions](std::string line) {
        std::smatch sm;
        std::regex_match(line, sm, re);

        char rega = ' ';
        int inta = 0;
        if (sm[2].length() == 1 && std::isalpha(sm[2].str()[0])) {
            rega = sm[2].str()[0];
        } else {
            inta = std::stoi(sm[2]);
        }
        char regb = ' ';
        int intb = 0;
        if (sm[5].length() == 1 && std::isalpha(sm[5].str()[0])) {
            regb = sm[5].str()[0];
        } else if (sm[5].length() > 1) {
            intb = std::stoi(sm[5]);
        }
        instructions.push_back(Instruction{ str_to_opcode(sm[1]), rega, regb, inta, intb});
    });

    int part1 = run_program(instructions, 0);
    int part2 = run_program(instructions, 1);

    return {part1,part2};
}

int reg_to_index(char reg) {
    return (int)(reg - 'a');
}

int run_program(std::vector<Instruction>& instructions, int initRegA) {
    std::vector<int> registers{initRegA,0};
    int ip = 0, icount = instructions.size();
    while (ip < icount) {
        Instruction inst = instructions[ip];
        int reg;
        switch (inst.Opcode) {
            case Opcode::hlf:
                reg = reg_to_index(inst.RegA);
                registers[reg] /= 2;
                ip++;
                break;
            case Opcode::tpl:
                reg = reg_to_index(inst.RegA);
                registers[reg] *= 3;
                ip++;
                break;
            case Opcode::inc:
                reg = reg_to_index(inst.RegA);
                registers[reg] += 1;
                ip++;
                break;
            case Opcode::jmp:
                ip += inst.ValA;
                break;
            case Opcode::jie:
                reg = reg_to_index(inst.RegA);
                ip += (registers[reg] % 2 == 0) ? inst.ValB : 1;
                break;
            case Opcode::jio:
                reg = reg_to_index(inst.RegA);
                ip += (registers[reg] == 1) ? inst.ValB : 1;
                break;
            default:
                std::cout << "Unknown instruction at ip=" << ip << ", Opcode=" << (int)inst.Opcode << "\n";
        }
    }

    return registers[1];
}