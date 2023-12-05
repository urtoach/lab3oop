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
    _Type type = static_cast<_Type>(data_[adress]);
    TypeTable table;
    size_t size_type = table.sizeof_[static_cast<size_t>(type)];

    std::vector<uint8_t> bin_value(size_type);
    for (size_t i = 0; i < size_type; i++){
        bin_value.push_back(data_[adress + 1 + i]);
    }
    return Data({type, size_type}, bin_value);
}

void Memory::write(size_t adress, const Data& value){
    size_t size_type = value.getType().size_;

    data_[adress] = static_cast<size_t>(value.getType().type_);

    for (size_t i = 0; i < size_type; i++){
        data_[adress + 1 + i] = value.getBinary()[i];
    }
}

void Memory::write(const Data& value) {
    size_t size_type = value.getType().size_;
    size_t adress = data_.size();

    data_[adress] = static_cast<size_t>(value.getType().type_);

    for (size_t i = 0; i < size_type; i++){
        data_[adress + 1 + i] = value.getBinary()[i];
    }
}

void Memory::write(const std::vector<uint8_t>& bin_value) {
    data_.insert(data_.end(), bin_value.begin(), bin_value.end());
}

void Memory::write(size_t address, const std::vector<uint8_t>& bin_value) {
    if (address > data_.size()) {
        data_.resize(address, 0);
    }
    data_.insert(data_.begin() + address, bin_value.begin(), bin_value.end());
}

//=====================================================//

// ProgramMemory
// other methods
void ProgramMemory::showProgram() {
    for (size_t i = 0; i < getData().size(); ++i) {
        std::cout << "address " << i << ": " << getData()[i] << std::endl;
    }
}

void ProgramMemory::editProgram() {
    if (!getData().empty()) {
    }
}

// DataMemory
void DataMemory::dump() {
    std::cout << "Dumping data..." << std::endl;
    std::ofstream outputFile("data_dump.txt");
    if (outputFile.is_open()) {
        for (size_t i = 0; i < getData().size(); ++i) {
            outputFile << "Address " << i << ": " << getData()[i] << std::endl;
        }
        outputFile.close();
        std::cout << "Data dumped successfully." << std::endl;
    } else {
        std::cout << "Unable to open the file for dumping data." << std::endl;
    }
}