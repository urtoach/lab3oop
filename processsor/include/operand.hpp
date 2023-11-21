#ifndef OPERAND_H
#define OPERAND_H


#include <registers.hpp>

// 
enum class OperandType{
    REGISTER_OPERAND,
    MEMORY_OPERAND,
    IMMEDIATE_OPERAND
};

//
class Label {
private:
    std::string id_;
    size_t adress_;
public:
    const std::string getId();
    uint64_t getAdres();
};

// parent class
class OperandDescriptor {
private:
    unsigned char code_;
public:
    OperandType getType();
    virtual uint64_t getValue() const = 0;
};

// child classes
class RegisterOperand: public OperandDescriptor {
private:
    GPRegister register_;
public:
    uint64_t getValue() const override;
};

class MemoryOperand: public OperandDescriptor {
private:
    size_t adress_;
public:
    uint64_t getValue() const override;
};

class ImmediateOperand: public OperandDescriptor {
private:
    uint64_t value_;
public:
    uint64_t getValue() const override;
};

#endif //OPERAND_H