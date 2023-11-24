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
    unsigned char code_;
public:
    // destructor
    virtual ~OperandDescriptor() = default;

    // getters
    OperandType getType() const;
    unsigned int getCode() const;

    virtual uint64_t getValue() const;
    virtual void setValue(uint64_t value);

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
    uint64_t getValue() const override;

    // setter
    void setRegister(const GPRegister name);
    void setValue(uint64_t value) override;
};

class MemoryOperand: public OperandDescriptor {
private:
    size_t adress_;
public:
    // constructor
    MemoryOperand(size_t adress);

    // getter
    size_t getAdress() const;
    uint64_t getValue() const override;

    // setter
    void setAdress(const size_t adress);
    void setValue(uint64_t value) override;
};

class ImmediateOperand: public OperandDescriptor {
private:
    uint64_t value_;
public:
    // constructors
    ImmediateOperand(uint64_t value);
    
    // getter
    uint64_t getValue() const override;

    // setter
    void setValue(uint64_t value) override;
};

#endif //OPERAND_H