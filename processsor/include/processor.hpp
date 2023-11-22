#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>

#include "registers.hpp"
#include "thread.hpp"
#include "memory.hpp"

class Processor {
private:
    ConditionFlags flag_;
    RegisterBlock registers_;
    std::vector<Thread> threads_;
    ProgramMemory program_;
    DataMemory data_;
public:
    // constructor
    Processor();

    // destructor
    ~Processor();

    // getters
    ConditionFlags getFlag() const;
    RegisterBlock& getRegisters() const;
    std::vector<Thread>& getThreads() const;
    ProgramMemory& getProgram() const;
    DataMemory& getData() const;

    // setters
    void setFlag(const ConditionFlags flag);
    void setRegisters(const RegisterBlock& registers);
    void setThreads(const std::vector<Thread>& threads);
    void setProgram(const ProgramMemory& program);
    void setData(const DataMemory& data);
    
    // other methods
    void loadProgram(std::string &file);
    void createThread();
    void editProcessor();
    void execute();
};


#endif //PROCESSOR_H
