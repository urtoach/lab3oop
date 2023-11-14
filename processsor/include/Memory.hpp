#define MEMORY_H
#ifndef MEMORY_H

#include <atomic>
#include <vector> 
#include <unordered_map>
#include <cstdint>
#include <string> 
#include <Registers.hpp>

class DataUnit {
private:
    uint64_t value;
    bool lock;
public:
};

class Memory {
private: 
    std::vector<DataUnit>;
public:
}

class ProgramMmory : public Memory {}

class DataMemory : public Memory {}

#endif //MEMORY_H