#ifndef OPERAND_H
#define OPERAND_H


#include <registers.hpp>

// 
enum class OperandType{
    REGISTER_OPERAND = 253,
    MEMORY_OPERAND,
    IMMEDIATE_OPERAND
};

//
class Label {
private:
    std::string id_;
    size_t adress_;
public:
    // getters
    std::string& getId() const;
    size_t getAdress() const;
    // setters
    void setId(const std::string& id);
    void setAdress(const size_t adress);
};

// parent class
class OperandDescriptor {
private:
    unsigned char code_;
public:
    // getters
    OperandType getType() const;
    unsigned int getCode() const;
    // setters
    // other methods
};

// child classes
class RegisterOperand: public OperandDescriptor {
private:
    GPRegister register_;
public:
    GPRegister getValue() const;
};

class MemoryOperand: public OperandDescriptor {
private:
    size_t adress_;
public:
    size_t getAdress() const;
};

class ImmediateOperand: public OperandDescriptor {
private:
    uint64_t value_;
public:
    uint64_t getValue() const;
};

#endif //OPERAND_H