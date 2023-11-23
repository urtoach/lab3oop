#ifndef MEMORY_H
#define MEMORY_H

#include <atomic>
#include <vector> 
#include <unordered_map>
#include <cstdint>
#include <string> 
#include <registers.hpp>

class DataUnit {
private:
    uint64_t value_;
public:
    // constructor
    DataUnit(uint64_t value);

    // getters
    uint64_t getValue() const;
    // setters
    void setValue(const uint16_t value);
};

class Memory {
private: 
    std::vector<DataUnit> data_;
public:
    // constructor
    Memory(const std::vector<DataUnit>& data);

    // destructor
    virtual ~Memory() = default;
    
    // getters
    std::vector<DataUnit> getData() const;

    // setters
    void setData(const std::vector<DataUnit>& data);

    // other methods
    DataUnit read(size_t adress);
    void write(size_t adress, uint64_t value);
};

class ProgramMemory : public Memory {
public:
    void showProgram();
    void editProgram();
};

class DataMemory : public Memory {
    void dump();
};

#endif //MEMORY_H