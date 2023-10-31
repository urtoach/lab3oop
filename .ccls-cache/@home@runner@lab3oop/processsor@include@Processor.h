#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "ControlUnit.h"
#include "RegisterBlock.h"
#include "DataMemory.h"
#include "Program.h"

class Processor {
private:
    ControlUnit controlUnit;
    RegisterBlock registerBlock;
    ProgramMemory programMemory;
    DataMemory dataMemory;
public:
    Processor();
    void editProcessorModel();
    void executeProgram(const Program& program);
};

#endif // PROCESSOR_H