#ifndef DECODER_H
#define DECODER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <functional>

#include "command.hpp"
#include "memory.hpp"


using CommandCreator = std::function<std::unique_ptr<CommandDescriptor>()>;

class CodeTable {
private:
    std::unordered_map<unsigned char, CommandCreator> opcode_to_command_;
public:
// constructor
    CodeTable();
// destructor
    std::unique_ptr<CommandDescriptor> commandCreate(unsigned char opcode);
// getters
// setters
};

//example
//std::unique_ptr<CommandDescriptor> command = op_table.commandCreate(0x01);

class Decoder {
private:
    ProgramMemory program_;
    CodeTable table_;
public:
};

#endif //DECODER_H