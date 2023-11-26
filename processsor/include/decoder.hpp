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
    std::unordered_map<uint8_t, CommandCreator> opcode_to_command_;
public:
    // constructor
    CodeTable();
    // destructor
    // other methods
    std::unique_ptr<CommandDescriptor> commandCreate(uint8_t opcode);
};

//example
//std::unique_ptr<CommandDescriptor> command = op_table.commandCreate(0x01);

class Decoder {
private:
    std::shared_ptr<Register> program_counter_;
    std::shared_ptr<ProgramMemory> program_;
    CodeTable table_;
public:
    // constructor
    Decoder(const Register pc);
    Decoder(const Register pc, ProgramMemory& program);

    // getter
    Register getPC() const;
    // setter
    void setPC(const Register pc);
    // other methods
    void decoder();
};

#endif // DECODER_H