#define COMMAND_H
#ifndef COMMAND_H

#include <string>
#include <Operand.hpp>

//
class Label {
private:
    std::string id;
    size_t adress;
public:
    const std::string getId();
    uint64_t getAdres();
};

// granny for commands
class CommandDescriptor {
private:
    Label label;
    uint64_t code;
public:
    virtual void execute() = 0;
};

// mommies for commands
class UnaryCommand : public CommandDescriptor {
private:
    OperandDescriptor operand;
};

class BinaryCommand : public CommandDescriptor {
private:
    OperandDescriptor operand1;
    OperandDescriptor operand2;
}

class JumpCommand : public CommandDescriptor {
private:
    Label jumpLabel;
} 

class DataDeclarationCommand : public CommandDescriptor {
private: 
};

class ThreadInitializationCommand : public CommandDescriptor {
private: 
    Label targetLabel;
}

class ThreadTermination : public CommandDescriptor {
private:
};

// commands
// unary commands
class INC : public UnaryCommand {};
class DEC : public UnaryCommand {};
class NOT : public UnaryCommand {};
class SHL : public UnaryCommand {};
class SHR : public UnaryCommand {};
class RET : public UnaryCommand {};
class HLT : public UnaryCommand {};
class JE : public UnaryCommand {};
class JNE : public UnaryCommand {};

// binary commands
class ADD : public BinaryCommand {};
class SUB : public BinaryCommand {};
class AND : public BinaryCommand {};
class OR : public BinaryCommand {};
class XOR : public BinaryCommand {};
class MOV : public BinaryCommand {};
class JG : public BinaryCommand {};
class JGE : public BinaryCommand {};
class JL : public BinaryCommand {};
class JLE : public BinaryCommand {};

// jump commands 
class JMP : public JumpCommand {};

// data declaration commands
class DB : public DataDeclarationCommand {};
class DW : public DataDeclarationCommand {};
class DD : public DataDeclarationCommand {};

#endif //COMMAND_H