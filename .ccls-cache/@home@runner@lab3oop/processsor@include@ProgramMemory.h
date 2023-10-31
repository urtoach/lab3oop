#ifndef PROGRAMMEMORY_H
#define PROGRAMMEMORY_H

#include <vector>
#include "Command.h"

class ProgramMemory {
private:
    std::vector<Command> program;
public:
    ProgramMemory();
    void addCommand(const Command& command);
    void editCommand(int index, const Command& command);
    Command getCommand(int index);
    void showProgram();
};

#endif // PROGRAMMEMORY_H