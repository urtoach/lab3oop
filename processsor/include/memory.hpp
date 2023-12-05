#ifndef MEMORY_H
#define MEMORY_H

#include <atomic>
#include <vector> 
#include <unordered_map>
#include <cstdint>
#include <string> 
#include <registers.hpp>
#include "memorytype.hpp"

 
class Memory {
protected: 
    std::vector<uint8_t> data_;
public:
    // constructor
    Memory(const std::vector<uint8_t>& data);

    // destructor
    ~Memory();
    
    // getters
    std::vector<uint8_t> getData() const;
    size_t getSize() { return data_.size(); }

    // setters
    void setData(const std::vector<uint8_t>& data);

    // other methods
    Data read(size_t adress);
    void write(const Data& bin_value);
    void write(size_t adress, const Data& bin_value);
    void write(const std::vector<uint8_t>& bin_value);
    void write(size_t adress, const std::vector<uint8_t>& bin_value);
    //void dump();
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