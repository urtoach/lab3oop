#include "../include/command.hpp"

// CommandDescriptor
Label CommandDescriptor::getLabel() const {
    return label_;
}

void CommandDescriptor::setLabel(const Label& label) {
    label_ = label;
}

//=======================================================// 

// UnaryCommand
std::shared_ptr<OperandDescriptor> UnaryCommand::getOperand() const {
    return operand_;
}

void UnaryCommand::setOperand(const std::shared_ptr<OperandDescriptor>& operand) {
    operand_ = operand;
}

//=======================================================// 

// BinaryCommand
BinaryCommand::BinaryCommand(const std::shared_ptr<OperandDescriptor>& operand1,
        const std::shared_ptr<OperandDescriptor>& operand2) {
    operands_[0] = operand1;
    operands_[1] = operand2;
}

std::array<std::shared_ptr<OperandDescriptor>, 2> BinaryCommand::getOperands() const {
    return operands_;
}

void BinaryCommand::setOperands(const std::shared_ptr<OperandDescriptor>& operand1,
        const std::shared_ptr<OperandDescriptor>& operand2) {
    operands_[0] = operand1;
    operands_[1] = operand2;
}

//=======================================================// 

// JumpCommand
Label JumpCommand::getJumpLabel() const {
    return jump_label_;
}

void JumpCommand::setJumpLabel(const Label& jump_label) {
    jump_label_ = jump_label;
}

//=======================================================// 

// ThreadInitializationCommand

//=======================================================// 

// ThreadTerminationCommand

//=======================================================// 

// INC
void INCFunc::execute() {
    UnaryCommand::operand_;
}