#include "../include/processor.hpp"
#include "../include/decoder.hpp"
#include "../include/interpreter.hpp"

// Processor
// constructor
Processor::Processor() {
    flags_->fill(false);
}

//====================================================//

// destructor

// getters
std::shared_ptr<std::array<bool, 4>> Processor::getFlags() {
    return flags_;
}

RegisterBlock Processor::getRegisters() {
    return registers_;
}

std::vector<Thread> Processor::getThreads() const {
    return threads_;
}

ProgramMemory Processor::getProgram() {
    return program_;
}

DataMemory Processor::getData() {
    return data_;
}

//====================================================//

// setters 
void Processor::setFlags(const std::array<bool, 4> flags) {
    for (size_t i = 0; i < flags.size(); i++){
        (*flags_)[i] = flags[i];
    }
}

void Processor::setRegisters(const RegisterBlock& registers){
    registers_ = registers;
}

void Processor::setThreads(const std::vector<Thread>& threads) {
    threads_ = threads;
}

void Processor::setProgram(const ProgramMemory& program) {
    program_ = program;
}

void Processor::setData(const DataMemory& data) {
    data_ = data;
}

//====================================================//

// other methods
void loadProgram(std::string &filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "unable to open file: " << filename << std::endl;
        throw std::runtime_error("unable to open file");
    }
    parser(file);
}

//====================================================//

