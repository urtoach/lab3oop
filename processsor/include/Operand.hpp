#define OPERAND_H
#ifndef OPERAND_H

#include <Registers.hpp>

// 
enum class OperandType{
    REGISTER_OPERAND,
    MEMORY_OPERAND,
    IMMEDIATE_OPERAND
};

// parent class
class OperandDescriptor {
public:
    OperandType getType();
    uint64_t getValue() const = 0;
};

// child classes
class RegisterOperand: public OperandDescriptor {
private:
    GPRegister register;
public:
    uint64_t getValue() const override;
}

class MemoryOperand: public OperandDescriptor {
private:
    size_t adress;
public:
    uint64_t getValue() const override;
}

class ImmediateOperand: public OperandDescriptor {
private:
    uint64_t value;
public:
    uint64_t getValue() const override;
}

#endif //OPERAND_H