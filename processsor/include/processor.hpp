#define PROCESSOR_H
#ifndef PROCESSOR_H

#include <vector>
#include <registers.hpp>
#include <threads.hpp>
#include <memory.hpp>

class Processor {
private:
    ConditionFlags flag;
    RegisterBlock registers;
    std::vector<Thread>;
    ProgramMemory program;
    DataMemory data;

public:
// getters
    
// setters
    void loadProgram(std::ofstream &file);
    void createThread();
    void editProcessor();
    void execute();
};


#endif //PROCESSOR_H
