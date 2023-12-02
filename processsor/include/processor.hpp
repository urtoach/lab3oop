#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <array>
#include <memory>

#include "registers.hpp"
#include "thread.hpp"
#include "memory.hpp"
#include "command.hpp"

constexpr int NUMBER_OF_FLAGS = 4;

class Processor {
private:
    StatCode stat_;
    std::shared_ptr<std::array<bool, NUMBER_OF_FLAGS>> flags_; // = std::make_shared<std::array<bool, 4>>();;
    RegisterBlock registers_;
    std::vector<Thread> threads_;
    ProgramMemory program_;
    DataMemory data_;
    Interpreter interpreter_;
public: 
    // constructor
    Processor();

    // destructor
    ~Processor();

    // getters
    std::shared_ptr<std::array<bool, NUMBER_OF_FLAGS>> getFlags();
    RegisterBlock getRegisters();
    std::vector<Thread> getThreads() const;
    ProgramMemory getProgram();
    DataMemory getData();
    //Memory getProgramMemory();
    //Memory getDataMemory();

    // setters
    void setFlags(const std::array<bool, NUMBER_OF_FLAGS> flags);
    void setRegisters(const RegisterBlock& registers);
    void setThreads(const std::vector<Thread>& threads);
    void setProgram(const ProgramMemory& program);
    void setData(const DataMemory& data);
    
    // other methods
    void loadProgram(std::string &file, Interpreter& interpreter);
    void createThread();
    void editProcessor();
    void execute();
};


#endif // PROCESSOR_H
