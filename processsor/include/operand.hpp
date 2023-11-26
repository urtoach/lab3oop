#ifndef OPERAND_H
#define OPERAND_H

#include "memorytype.hpp"
#include <registers.hpp>
#include <iostream>

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
    // constructors
    Label(std::string& id);
    Label(std::string& id, size_t adress);

    // destructors

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
    uint8_t code_;
public:
    // destructor
    virtual ~OperandDescriptor() = default;

    // getters
    OperandType getType() const;
    uint8_t getCode() const;

    template<class Type>
    virtual Data<Type> getValue() const;
    virtual void setValue(Data<Type> value);

    // other methods
};

// child classes
class RegisterOperand: public OperandDescriptor {
private:
    GPRegister register_;
public:
    // constructor
    RegisterOperand(GPRegister reg);

    // getter
    GPRegister getRegister() const;

    template <class Type>
    Data<Type> getValue() const override;

    // setter
    void setRegister(const GPRegister name);

    template <class Type>
    void setValue(Data<Type> value) override;
};

class MemoryOperand: public OperandDescriptor {
private:
    size_t adress_;
public:
    // constructor
    MemoryOperand(size_t adress);

    // getter
    size_t getAdress() const;

    template <class Type>
    Data<Type> getValue() const override;

    // setter
    void setAdress(const size_t adress);

    template <class Type>
    void setValue(Data<Type> value) override;
};

template <class Type>
class ImmediateOperand: public OperandDescriptor {
private:
    Data<Type> value_;
public:
    // constructors
    ImmediateOperand(Data<Type> value);
    
    // getter
    template <class Type>
    Data<Type> getValue() const override;

    // setter
    void setValue(Data<Type> value) override;
};

#endif // OPERAND_H