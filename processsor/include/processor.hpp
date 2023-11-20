#define PROCESSOR_H
#ifndef PROCESSOR_H

#include <vector>
#include <registers.hpp>
#include <threads.hpp>
#include <memory.hpp>

class Processor {
private:
    ConditionFlags flag_;
    RegisterBlock registers_;
    std::vector<Thread> threads_;
    ProgramMemory program_;
    DataMemory data_;

public:
// getters
    
// setters
    void loadProgram(std::ofstream &file);
    void createThread();
    void editProcessor();
    void execute();
};


#endif //PROCESSOR_H
