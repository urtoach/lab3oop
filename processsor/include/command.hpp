#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <array>


#include <operand.hpp>
#include <memory>

// granny for commands
class CommandDescriptor {
private:
    Label label_;
public:
    // constructor
    CommandDescriptor();
    // destructor
    virtual ~CommandDescriptor() = default;
    
    // getters
    Label getLabel() const;
    
    // setters
    void setLabel(const Label& label); 
    
    // other methods
    virtual void execute() = 0;
};

// mommies for commands
class UnaryCommand : public CommandDescriptor {
protected:
    std::shared_ptr<OperandDescriptor> operand_;
public:
    // constructor
    UnaryCommand(const std::shared_ptr<OperandDescriptor>& operand) : operand_(operand) {};
    
    // destructor
    virtual ~UnaryCommand() = default;
    
    // getters
    std::shared_ptr<OperandDescriptor> getOperand() const;
    
    // setters
    void setOperand(const std::shared_ptr<OperandDescriptor>& operand);
};

class BinaryCommand : public CommandDescriptor {
protected:
    std::array<std::shared_ptr<OperandDescriptor>, 2> operands_;
public:
    // constructor
    BinaryCommand(const std::shared_ptr<OperandDescriptor>& operand1,
                  const std::shared_ptr<OperandDescriptor>& operand2);
    
    // destructor
    virtual ~BinaryCommand() = default;
    
    // getters
    std::array<std::shared_ptr<OperandDescriptor>,2> getOperands() const;
    
    // setters
    void setOperands(const std::shared_ptr<OperandDescriptor>& operand1,
         const std::shared_ptr<OperandDescriptor>& operand2);
};

class JumpCommand : public CommandDescriptor {
private:
    Label jump_label_;
public:
    // constructor
    JumpCommand(const Label& jump_label) : jump_label_(jump_label) {};
    // destructor
    virtual ~JumpCommand() = default;
    
    // getters
    Label getJumpLabel() const;
    
    // setters
    void setJumpLabel(const Label& jump_label);
};

class DataDeclarationCommand : public CommandDescriptor {
private: 
public:
    // constructor
    
    // destructor
    virtual ~DataDeclarationCommand() = default;
    
    // getters
    
    // setters
};

class ThreadInitializationCommand : public CommandDescriptor {
private: 
    Label target_label_;
public:
    // constructor
    
    // destructor
    virtual ~ThreadInitializationCommand() = default;
    
    // getters
    Label getTargetLabel() const;
    
    // setters
    void setTargetLabel(const Label& target_label);
};

class ThreadTerminationCommand : public CommandDescriptor {
private:
public:
    // constructor
    // destructor
    virtual ~ThreadTerminationCommand() = default;
    // getters
    // setters
};

// commands
// unary commands
class INCFunc : public UnaryCommand {
public:
    void execute() override;
};

class DECFunc : public UnaryCommand {
public:
    void execute() override;
};

class NOTFunc : public UnaryCommand {
public:
    void execute() override;
};

class SHLFunc : public UnaryCommand {
public:
    void execute() override;
};

class SHRFunc : public UnaryCommand {
public:
    void execute() override;
};

class RETFunc : public UnaryCommand {
public:
    void execute() override;
};

class HLTFunc : public UnaryCommand {
public:
    void execute() override;
};

class CALLFunc : public UnaryCommand {
public:
    void execute() override;
};

// binary commands
class ADDFunc : public BinaryCommand {
public:
    void execute() override;
};

class SUBFunc : public BinaryCommand {
public:
    void execute() override;
};

class ANDFunc : public BinaryCommand {
public:
    void execute() override;
};

class ORFunc : public BinaryCommand {
public:
    void execute() override;
};

class XORFunc : public BinaryCommand {
public:
    void execute() override;
};

class MOVFunc : public BinaryCommand {
public:
    void execute() override;
};

class CMPFunc : public BinaryCommand {
public:
    void execute() override;
};

// jump commands 
class JMPFunc : public JumpCommand {
public:
    void execute() override;
};

class JEFunc : public JumpCommand {
public:
    void execute() override;
};

class JNEFunc : public JumpCommand {
public:
    void execute() override;
};

class JGFunc : public JumpCommand {
public:
    void execute() override;
};

class JGEFunc : public JumpCommand {
public:
    void execute() override;
};

class JLFunc : public JumpCommand {
public:
    void execute() override;
};

class JLEFunc : public JumpCommand {
public:
    void execute() override;
};

// data declaration commands
class DBFunc : public DataDeclarationCommand {
public:
    void execute() override;
};

class DWFunc : public DataDeclarationCommand {
public:
    void execute() override;
};

class DDFunc : public DataDeclarationCommand {
public:
    void execute() override;
};


#endif //COMMAND_H