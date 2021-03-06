#ifndef MONTADOR_H
#define MONTADOR_H

//includes and namespaces
#include "utils.h"

//definitions
#define COMMENT_DELIMITER ";"
#define LABEL_DELIMITER ":"
#define MEM_SIZE "1000"

class Program {
    public:
        vector<vector<string>> lines;
        size_t amountOfLines;
        int amountOfCommands;
        Program() {
            amountOfLines = 0;
            amountOfCommands = 0;
        }
        void addLine(vector<string> line) {
            lines.push_back(line);
            amountOfLines++;
            amountOfCommands = amountOfCommands + line.size();
        }
};

//assembler functions
int assemble(char *fileName);
void firstStep(ifstream &programFile, Program &program, StringIntHash &symbolHash);
void secondStep(Program &program, StringIntHash &symbolHash, string &machineCommands);
void genAssemblerOutput(string machineCommands, int machineCommandAmount, StringIntHash &symbolHash);
vector<string> getMeaningfulVec(string &line);

//instructions
const map<string, int> Instructions {
    {"HALT",    0}, // Stop the program
    {"LOAD",    1}, // Reg[R] <- Mem[M + PC]
    {"STORE",   2}, // Mem[M + PC] <- Reg[R]
    {"READ",    3}, // Reg[R] <- input
    {"WRITE",   4}, // output <- Reg[R]
    {"COPY",    5}, // Reg[R1] <- Reg[R2], update PSW
    {"PUSH",    6}, // SP <- SP - 1; Mem[SP] <- Reg[R]
    {"POP",     7}, // Reg[R] <- Mem[SP]; SP <- SP + 1;
    {"ADD",     8}, // Reg[R1] <- Reg[R1] + Reg[R2], update PSW
    {"SUB",     9}, // Reg[R1] <- Reg[R1] - Reg[R2], update PSW
    {"MUL",    10}, // Reg[R1] <- Reg[R1] * Reg[R2], update PSW
    {"DIV",    11}, // Reg[R1] <- Reg[R1] / Reg[R2], update PSW
    {"MOD",    12}, // Reg[R1] <- Reg[R1] % Reg[R2], update PSW
    {"AND",    13}, // Reg[R1] <- Reg[R1] & Reg[R2], update PSW
    {"OR",     14}, // Reg[R1] <- Reg[R1] | Reg[R2], update PSW
    {"NOT",    15}, // Reg[R1] <- ~Reg[R1], update PSW
    {"JUMP",   16}, // PC <- PC + M
    {"JZ",     17}, // If PSW[0] == 1, PC <- PC + M
    {"JN",     18}, // If PSW[1] == 1, PC <- PC + M
    {"CALL",   19}, // SP <- SP - 1; Mem[SP] <- PC; PC <- PC + M
    {"RET",    20}, // PC <- Mem[SP]; SP <- SP + 1
};

//pseudo-instructions
#define PSEUDO_INST_WORD "WORD"
#define PSEUDO_INST_END "END"

//registers
const map<string, int> Registers {
    {"R0",      0},
    {"R1",      1},
    {"R2",      2},
    {"R3",      3}
};

#endif
