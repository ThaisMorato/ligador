#include <iostream>
#include "ligador.h"

int link(char *fileNames[], int fileAmount) {
    StringIntHash symbolHash;
    vector<string> program;
    int machineCommandAmount = 0;

    for(int i = 0; i < fileAmount; i++) {
        char *fileName = fileNames[i];
        ifstream programFile(fileName);
        machineCommandAmount += firstStep(programFile, program, machineCommandAmount, symbolHash);
        programFile.close();
    }
    string machineCommands = secondStep(program, symbolHash);
    genLinkerOutput(machineCommands, machineCommandAmount, symbolHash);
    return 0;
}

void genLinkerOutput(string machineCommands, int machineCommandAmount, StringIntHash &symbolHash) {
    int programBegin = symbolHash.getCorrespondent("main");
    cout << "MV-EXE\n\n";
    cout << to_string(machineCommandAmount) + " 0 999 " + to_string(programBegin) + "\n\n";
    cout << machineCommands + "\n";
}

int firstStep(ifstream &programFile, vector<string> &program, int programStart, StringIntHash &symbolHash) {
    string line;

    //command line
    vector<string> currentProgram;
    getline(programFile, line);
    tokenize(line,' ', currentProgram);
    program.insert(program.end(), currentProgram.begin(), currentProgram.end());
    line.clear();

    for(int i = 0; i < program.size(); i++) {
        cout << program[i] << "|";
    }
    cout << endl;

    //amount of commands line
    getline(programFile, line);
    int programSize = stoi(line);
    line.clear();

    //symbol table lines
    string label;
    string valueString;
    vector<string> labelLine;
    int value;
    while(getline(programFile, line)) {
        tokenize(line,' ', labelLine);
        label = labelLine[0];
        value = stoi(labelLine[1]);
        symbolHash.addToHash(label, value + programStart);
        labelLine.clear();
        line.clear();
    }

    return programSize;
}

string secondStep(vector<string> &program, StringIntHash &symbolHash) {
    string command;
    int correspondent;
    int machineCommand;
    string machineCommands;
    int currentCommand = 1;
    for(size_t i = 0; i < program.size(); i++) {
        command = program[i];
        correspondent = symbolHash.getCorrespondent(command);
        if(correspondent >= 0) {
            machineCommand = correspondent - (currentCommand + 1);
            machineCommands = machineCommands + to_string(machineCommand) + " ";
        }
        else {
            machineCommands = machineCommands + command + " ";
        }
        currentCommand++;
    }
    return machineCommands;
}

void tokenize(string const &str, const char delim, vector<string> &out)
{
    size_t start;
    size_t end = 0;
 
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}