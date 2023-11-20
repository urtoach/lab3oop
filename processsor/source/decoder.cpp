#include <../include/decoder.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

// CodeTable methods
CodeTable::CodeTable() {
    opcode_to_table_[1] = []() { return std::make_unique<AddFunc>(); };
    // 
}

std::unique_ptr<CommandDescriptor> CodeTable::commandCreate(unsigned char opcode){
    auto it = opcode_to_table_.find(opcode);
    if (it == opcode_to_table_.end()) {
        return it->second();
    }
    throw std::runtime_error("invalid opcode");
}

