#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include "ProgramMemory.h"
#include "ExecutionDevice.h"

class ControlUnit {
private:
    ProgramMemory& programMemory;
    ExecutionDevice& executionDevice;
public:
    ControlUnit(ProgramMemory& programMemory, ExecutionDevice& executionDevice);
    void executeProgram();
};

#endif // CONTROLUNIT_H