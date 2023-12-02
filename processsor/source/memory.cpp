#include "../include/memory.hpp"
#include "../include/memorytype.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

//=====================================================//

// Memory
// constructor
Memory::Memory(const std::vector<uint8_t>& data){
    data_ = data; 
}

// getter
std::vector<uint8_t> Memory::getData() const {
    return data_;
}

// setter
void Memory::setData(const std::vector<uint8_t>& data){
    data_ = data;
}

// other methods 
Data Memory::read(size_t adress) {
    DataType type = static_cast<DataType>(data_[adress]);
    TypeTable table;
    size_t size_type = table.getSize(type);
    std::vector<uint8_t> bin_value(size_type);
    for (size_t i = 0; i < size_type; i++){
        bin_value.push_back(data_[adress + 1 + i]);
    }
    return Data(type, bin_value);
}

void Memory::write(size_t adress, Data value){
    TypeTable table;
    size_t size_type = table.getSize(value.getType());
    data_[adress] = static_cast<size_t>(value.getType());
    for (size_t i = 0; i < size_type; i++){
        data_[adress + 1 + i] = value.getBinary()[i];
    }
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