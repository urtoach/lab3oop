#include <decoder.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "../include/command.hpp"

// CodeTable methods
CodeTable::CodeTable() {
    opcode_to_command_[0x01] = []() { return std::make_unique<MOVFunc>(); };
    // arithmetic
    opcode_to_command_[0x02] = []() { return std::make_unique<ADDFunc>(); };
    opcode_to_command_[0x03] = []() { return std::make_unique<SUBFunc>(); };
    opcode_to_command_[0x04] = []() { return std::make_unique<INCFunc>(); };
    opcode_to_command_[0x05] = []() { return std::make_unique<DECFunc>(); };
    // logic
    opcode_to_command_[0x06] = []() { return std::make_unique<NOTFunc>(); };
    opcode_to_command_[0x07] = []() { return std::make_unique<ANDFunc>(); };
    opcode_to_command_[0x08] = []() { return std::make_unique<ORFunc>(); };
    opcode_to_command_[0x09] = []() { return std::make_unique<XORFunc>(); };
    opcode_to_command_[0x0A] = []() { return std::make_unique<CMPFunc>(); };
    // shifts
    opcode_to_command_[0x0B] = []() { return std::make_unique<SHLFunc>(); };
    opcode_to_command_[0x0C] = []() { return std::make_unique<SHRFunc>(); };
    // jumps
    opcode_to_command_[0x0D] = []() { return std::make_unique<JMPFunc>(); };
    opcode_to_command_[0x0E] = []() { return std::make_unique<JEFunc>(); };
    opcode_to_command_[0x0F] = []() { return std::make_unique<JNEFunc>(); };
    opcode_to_command_[0x10] = []() { return std::make_unique<JGFunc>(); };
    opcode_to_command_[0x11] = []() { return std::make_unique<JGEFunc>(); };
    opcode_to_command_[0x12] = []() { return std::make_unique<JLFunc>(); };
    opcode_to_command_[0x13] = []() { return std::make_unique<JLEFunc>(); };
    // data definition
    opcode_to_command_[0x14] = []() { return std::make_unique<DBFunc>(); };
    opcode_to_command_[0x15] = []() { return std::make_unique<DWFunc>(); };
    opcode_to_command_[0x16] = []() { return std::make_unique<DDFunc>(); };
    // misc
    opcode_to_command_[0x17] = []() { return std::make_unique<HLTFunc>(); };
    opcode_to_command_[0x18] = []() { return std::make_unique<RETFunc>(); };
    opcode_to_command_[0x19] = []() { return std::make_unique<CALLFunc>(); };
}

std::unique_ptr<CommandDescriptor> CodeTable::commandCreate(unsigned char opcode){
    auto it = opcode_to_command_.find(opcode);
    if (it == opcode_to_command_.end()) {
        return it->second();
    }
    throw std::runtime_error("invalid opcode");
}

