#define PROGRAM_H
#ifndef PROGRAM_H

#include <Command.h>

class Program {
private: 
    std::list<CommandDescription> commands;
public:
    void addCommand(CommandDescription &command);
    void removeCommand(CommandDescription &command);
};

class ProgramMemory {
private:
    Program program;
    size_t size;
public: 
    void editProgram();
    void showProgram();
    CommandDescripion getCurrentCommand();
    void + setProgramCounter(int address);
};

#endif //PROGRAM_H