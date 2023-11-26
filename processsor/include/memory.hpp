#ifndef MEMORY_H
#define MEMORY_H

#include <atomic>
#include <vector> 
#include <unordered_map>
#include <cstdint>
#include <string> 
#include <registers.hpp>

/* class DataUnit {
private:
    Data value_;
public:
    // constructor
    DataUnit(uint64_t value);

    // getters
    uint64_t getValue() const;
    // setters
    void setValue(uint64_t value);
}; */

class Memory {
private: 
    std::vector<uint8_t> data_;
public:
    // constructor
    Memory(const std::vector<uint8_t>& data);

    // destructor
    virtual ~Memory() = default;
    
    // getters
    std::vector<uint8_t> getData() const;

    // setters
    void setData(const std::vector<uint8_t>& data);

    // other methods
    std::vector<uint8_t> read(size_t adress);
    void write(size_t adress, std::vector<uint8_t> bin_value);
};


class ProgramMemory : public Memory {
public:
    void showProgram();
    void editProgram();
};

class DataMemory : public Memory {
    void dump();
};

#endif // MEMORY_H