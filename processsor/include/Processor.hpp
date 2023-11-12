#define PROCESSOR_H
#ifndef PROCESSOR_H

#include <vector>
#include <Registers.hpp>
#include <Threads.hpp>
#include <Memory.hpp>

class Processor {
private:
    ConditionFlags flag;
    RegisterBlock registers;
    std::vector<Thread>;
    Memory memory;

public:
// getters
// setters
};


#endif //PROCESSOR_H
