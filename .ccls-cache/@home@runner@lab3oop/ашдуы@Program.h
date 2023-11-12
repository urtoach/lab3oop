#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>
#include "Command.h"

class Program {
private:
    std::vector<Command> program;
public:
    void addCommand(const Command& command);
    void editCommand(int index, const Command& command);
    Command getCommand(int index);
    void showProgram();
};

#endif // PROGRAM_H