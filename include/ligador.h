#ifndef LIGADOR_H
#define LIGADOR_H

//includes and namespaces
#include "utils.h"

//linker functions
int link(char *fileNames[], int fileAmount);
int firstStep(ifstream &programFile, vector<string> &program, int programStart, StringIntHash &symbolHash);
void secondStep(vector<string> &program, StringIntHash &symbolHash, string &machineCommands);
void genLinkerOutput(string machineCommands, int machineCommandAmount, StringIntHash &symbolHash);
void tokenize(string const &str, const char delim, vector<string> &out);

#endif
