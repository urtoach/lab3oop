#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <operand.hpp>
#include <memory>

// granny for commands
class CommandDescriptor {
private:
    Label label_;
public:
    virtual ~CommandDescriptor() = default;
    virtual void execute() = 0;

    Label get
};

// mommies for commands
class UnaryCommand : public CommandDescriptor {
private:
    std::shared_ptr<OperandDescriptor> operand_;
};

class BinaryCommand : public CommandDescriptor {
private:
    std::shared_ptr<OperandDescriptor> operand1_;
    std::shared_ptr<OperandDescriptor> operand2_;
};

class JumpCommand : public CommandDescriptor {
private:
    Label jumpLabel_;
};

class DataDeclarationCommand : public CommandDescriptor {
private: 
};

class ThreadInitializationCommand : public CommandDescriptor {
private: 
    Label targetLabel_;
};

class ThreadTermination : public CommandDescriptor {
private:
};

// commands
// unary commands
class INCFunc : public UnaryCommand {};
class DECFunc : public UnaryCommand {};
class NOTFunc : public UnaryCommand {};
class SHLFunc : public UnaryCommand {};
class SHRFunc : public UnaryCommand {};
class RETFunc : public UnaryCommand {};
class HLTFunc : public UnaryCommand {};
class CALLFunc : public UnaryCommand {};

// binary commands
class ADDFunc : public BinaryCommand {};
class SUBFunc : public BinaryCommand {};
class ANDFunc : public BinaryCommand {};
class ORFunc : public BinaryCommand {};
class XORFunc : public BinaryCommand {};
class MOVFunc : public BinaryCommand {};
class CMPFunc : public BinaryCommand {};

// jump commands 
class JMPFunc : public JumpCommand {};
class JEFunc : public JumpCommand {};
class JNEFunc : public JumpCommand {};
class JGFunc : public JumpCommand {};
class JGEFunc : public JumpCommand {};
class JLFunc : public JumpCommand {};
class JLEFunc : public JumpCommand {};

// data declaration commands
class DBFunc : public DataDeclarationCommand {};
class DWFunc : public DataDeclarationCommand {};
class DDFunc : public DataDeclarationCommand {};

// class for create 
/*class CommandFactory {
public:
    static std::unique_ptr<CommandDescriptor> createAdd() {
      return std::make_unique<ADD>();
    }
}; */

// type for command instantiation func
//using OperationCreator = std::function<std::unique_ptr<Operation>()>;


#endif //COMMAND_H