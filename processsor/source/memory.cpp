#include "../include/memory.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

// DataUnit 
DataUnit::DataUnit(uint64_t value){
    value_ = value;
}

uint64_t DataUnit::getValue() const {
    return value_;
}

void DataUnit::setValue(const uint64_t value) {
    value_ = value;
}

//=====================================================//

// Memory
// constructor
Memory::Memory(const std::vector<DataUnit>& data){
    data_ = data; 
}

// getter
std::vector<DataUnit> Memory::getData() const {
    return data_;
}

// setter
void Memory::setData(const std::vector<DataUnit>& data){
    data_ = data;
}

// other methods 
DataUnit Memory::read(size_t adress) {
    return data_[adress];
}

void Memory::write(size_t adress, uint64_t value){
    data_[adress].setValue(value);
}

//=====================================================//

// ProgramMemory
// other methods
void ProgramMemory::showProgram() {
    for (size_t i = 0; i < getData().size(); ++i) {
        std::cout << "address " << i << ": " << getData()[i].getValue() << std::endl;
    }
}

void ProgramMemory::editProgram() {
    if (!getData().empty()) {
        getData()[0].setValue(0xFF);
    }
}

// DataMemory
void DataMemory::dump() {
    std::cout << "Dumping data..." << std::endl;
    std::ofstream outputFile("data_dump.txt");
    if (outputFile.is_open()) {
        for (size_t i = 0; i < getData().size(); ++i) {
            outputFile << "Address " << i << ": " << getData()[i].getValue() << std::endl;
        }
        outputFile.close();
        std::cout << "Data dumped successfully." << std::endl;
    } else {
        std::cout << "Unable to open the file for dumping data." << std::endl;
    }
}