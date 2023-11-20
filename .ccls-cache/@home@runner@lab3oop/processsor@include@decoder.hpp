#define DECODER_H
#ifndef DECODER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <command.hpp>

using OperationCreator = std::function<std::unique_ptr<CommandDescriptor>()>;

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

#endif //DECODER_H