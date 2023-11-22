#include <iostream>
#include <fstream>
#include <string>
#include "../include/interpreter.hpp"
#include "../include/processor.hpp"


// CommandTable methods
CommandTable::CommandTable(){
    mnemomic_to_opcode_["mov"] = 0x01;

    mnemomic_to_opcode_["add"] = 0x02;
    mnemomic_to_opcode_["sub"] = 0x03;
    mnemomic_to_opcode_["inc"] = 0x04;
    mnemomic_to_opcode_["dec"] = 0x05;

    mnemomic_to_opcode_["not"] = 0x06;
    mnemomic_to_opcode_["and"] = 0x07;
    mnemomic_to_opcode_["or"] = 0x08;
    mnemomic_to_opcode_["xor"] = 0x09;
    mnemomic_to_opcode_["cmp"] = 0x0A;

    mnemomic_to_opcode_["shl"] = 0x0B;
    mnemomic_to_opcode_["shr"] = 0x0C;

    mnemomic_to_opcode_["jmp"] = 0x0D;
    mnemomic_to_opcode_["je"] = 0x0E;
    mnemomic_to_opcode_["jne"] = 0x0F;
    mnemomic_to_opcode_["jg"] = 0x10;
    mnemomic_to_opcode_["jge"] = 0x11;
    mnemomic_to_opcode_["jl"] = 0x12;
    mnemomic_to_opcode_["jle"] = 0x13;

    mnemomic_to_opcode_["db"] = 0x14;
    mnemomic_to_opcode_["dw"] = 0x15;
    mnemomic_to_opcode_["dd"] = 0x16;

    mnemomic_to_opcode_["hlt"] = 0x17;
    mnemomic_to_opcode_["ret"] = 0x18;
    mnemomic_to_opcode_["call"] = 0x19;
}

unsigned char CommandTable::getOpcode(const std::string& opcode) const {
    auto it = mnemomic_to_opcode_.find(opcode);
    if (it == mnemomic_to_opcode_.end()) {
        return it->second;
    }
    return 0x00;
}


// other methods

void parser(const std::string filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "unable to open file: " << filename << std::endl;
        throw std::runtime_error("unable to open file");
    }
    std::string line;
    Processor processor;
    
    while (std::getline(file, line)) {
        // if empty or comment
        if (line.empty() || line.front() == ';') {
            continue;
        }
        if (line.back() == ':')
    }
    file.close();
}