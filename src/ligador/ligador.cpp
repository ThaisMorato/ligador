#include <iostream>
#include "ligador.h"

int link(char *fileNames[], int fileAmount) {
    StringIntHash symbolHash;
    vector<string> program;
    string machineCommands;
    int machineCommandAmount = 0;

    for(int i = 0; i < fileAmount; i++) {
        char *fileName = fileNames[i];
        ifstream programFile(fileName);
        machineCommandAmount += firstStep(programFile, program, machineCommandAmount, symbolHash);
        programFile.close();
    }
    secondStep(program, symbolHash, machineCommands);
    //genLinkerOutput(machineCommands, machineCommandAmount, symbolHash);
    return 0;
}

void genLinkerOutput(string machineCommands, int machineCommandAmount, StringIntHash &symbolHash) {
    int programBegin = symbolHash.getCorrespondent("main");
    //cout << "MV-EXE\n\n";
    cout << to_string(machineCommandAmount) + " 0 999 " + to_string(programBegin) + "\n\n";
    cout << machineCommands + "\n";
}

int firstStep(ifstream &programFile, vector<string> &program, int programStart, StringIntHash &symbolHash) {
    string line;
    size_t pos;

    // //MV-O line
    // getline(programFile, line);
    // line.clear();

    // //command line
    // string command;
    //getline(programFile, line);
    // while((pos = line.find(" ")) != string::npos) {
    //     command = line.substr(0, pos);
    //     if(!command.empty()) program.push_back(command);
    //     line.erase(0, pos + 1);
    // }
    
    getline(programFile, line);
    tokenize(line,' ', program );
    line.clear();

    //teste
    for(int i = 0; i < (int)program.size(); i++) {
        cout << program[i] + "|";
    }
    cout << endl;

    //amount of commands line
    getline(programFile, line);
    int programSize = stoi(line);
    line.clear();
    
    //symbol table lines
    // string label;
    // string valueString;
    // int value;
    // while(getline(programFile, line)) {
    //     pos = line.find(" ");
    //     label = line.substr(0, pos);
    //     line.erase(0, pos + 1);
    //     valueString = line.find(";");
    //     value = stoi(valueString);
    //     symbolHash.addToHash(label, value + programStart);
    // }

    return 0;
}

void secondStep(vector<string> &program, StringIntHash &symbolHash, string &machineCommands) {
    string command;
    int correspondent;
    int machineCommand;
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