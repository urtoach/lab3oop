#define MEMORY_H
#ifndef MEMORY_H

#include <atomic>
#include <vector> 
#include <unordered_map>
#include <cstdint>
#include <string> 
#include <registers.hpp>

class DataUnit {
private:
    uint64_t value;
public:
};

class Memory {
private: 
    std::vector<DataUnit>;
public:
    void read(size_t adress);
    void write(size_t adress, uint64_t value);
};

class ProgramMmory : public Memory {
public:
    void showProgram();
    void editProgram();
};

class DataMemory : public Memory {
    void dump();
    
};

#endif //MEMORY_H