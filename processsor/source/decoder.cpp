#include <decoder.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "../include/command.hpp"

// CodeTable methods
CodeTable::CodeTable() {
    opcode_to_command_[1] = []() { return std::make_unique<MOVFunc>(); };
    // arithmetic
    opcode_to_command_[2] = []() { return std::make_unique<ADDFunc>(); };
    opcode_to_command_[3] = []() { return std::make_unique<SUBFunc>(); };
    opcode_to_command_[4] = []() { return std::make_unique<INCFunc>(); };
    opcode_to_command_[5] = []() { return std::make_unique<DECFunc>(); };
    // logic
    opcode_to_command_[6] = []() { return std::make_unique<NOTFunc>(); };
    opcode_to_command_[7] = []() { return std::make_unique<ANDFunc>(); };
    opcode_to_command_[8] = []() { return std::make_unique<ORFunc>(); };
    opcode_to_command_[9] = []() { return std::make_unique<XORFunc>(); };
    opcode_to_command_[10] = []() { return std::make_unique<CMPFunc>(); };
    // shifts
    opcode_to_command_[11] = []() { return std::make_unique<SHLFunc>(); };
    opcode_to_command_[12] = []() { return std::make_unique<SHRFunc>(); };
    // jumps
    opcode_to_command_[13] = []() { return std::make_unique<JMPFunc>(); };
    opcode_to_command_[14] = []() { return std::make_unique<JEFunc>(); };
    opcode_to_command_[15] = []() { return std::make_unique<JNEFunc>(); };
    opcode_to_command_[16] = []() { return std::make_unique<JGFunc>(); };
    opcode_to_command_[17] = []() { return std::make_unique<JGEFunc>(); };
    opcode_to_command_[18] = []() { return std::make_unique<JLFunc>(); };
    opcode_to_command_[19] = []() { return std::make_unique<JLEFunc>(); };
    // data definition
    opcode_to_command_[20] = []() { return std::make_unique<DBFunc>(); };
    opcode_to_command_[21] = []() { return std::make_unique<DWFunc>(); };
    opcode_to_command_[22] = []() { return std::make_unique<DDFunc>(); };
    // misc
    opcode_to_command_[23] = []() { return std::make_unique<HLTFunc>(); };
    opcode_to_command_[24] = []() { return std::make_unique<RETFunc>(); };
    opcode_to_command_[25] = []() { return std::make_unique<CALLFunc>(); };
}

std::unique_ptr<CommandDescriptor> CodeTable::commandCreate(unsigned char opcode){
    auto it = opcode_to_command_.find(opcode);
    if (it == opcode_to_command_.end()) {
        return it->second();
    }
    throw std::runtime_error("invalid opcode");
}

