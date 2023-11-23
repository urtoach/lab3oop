#include "../include/command.hpp"
#include "iostream"

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
    if (UnaryCommand::getOperand()) {
        ++(*(operand_));
    }
    //throw std::invalid_argument("empty operand");
}

//=======================================================//

// DEC
void DECFunc::execute() {
    if (UnaryCommand::getOperand()) {
        --(*(operand_));
    }
    //throw std::invalid_argument("empty operand");
}

//=======================================================//

// NOT
void NOTFunc::execute() {
    if (UnaryCommand::getOperand()) {
        operand_ = ~(*(operand_));
    }
    //throw std::invalid_argument("empty operand");
}

//=======================================================//

// HLT
void HLTFunc::execute() {
    std::cout << "Processor halted." << std::endl;
    CommandDescriptor::setStat(StatCode::HLT);
}

//=======================================================//

// ADD
void ADDFunc::execute() {
    operands_[0] += operands_[1];
    //throw std::invalid_argument("empty operand");
}

//=======================================================//

// SUB
void SUBFunc::execute() {
    operands_[0] -= operands_[1];
    //throw std::invalid_argument("empty operand");
}

//=======================================================//

// AND
void ANDFunc::execute() {
    operands_[0] = operands_[0] & operands_[1];
    if (operands_[0] == 0) { (*flags_)[(size_t)ConditionFlags::ZF] = true; }
    else { (*flags_)[(size_t)ConditionFlags::ZF] = false; }
    //throw std::invalid_argument("empty operand");
}

//=======================================================//

// OR
void ORFunc::execute() {
    operands_[0] = operands_[0] | operands_[1];
    if (operands_[0] == 0) { (*flags_)[(size_t)ConditionFlags::ZF] = true; }
    else { (*flags_)[(size_t)ConditionFlags::ZF] = false; }
    //throw std::invalid_argument("empty operand");
}

//=======================================================//

// XOR
void XORFunc::execute() {
    std::shared_ptr<OperandDescriptor> result;
    *result = (~(*operands_[0]) & operands_[1]) | (~(operands_[1]) & operands_[0]); 
    *operands_[0] = *result;
    if (operands_[0] == 0) { (*flags_)[(size_t)ConditionFlags::ZF] = true; }
    else { (*flags_)[(size_t)ConditionFlags::ZF] = false; }
    //throw std::invalid_argument("empty operand");
}

//=======================================================//

// MOV
void MOVFunc::execute() {
    operands_[0] = operands_[1];
    //throw std::invalid_argument("empty operand");
}

//=======================================================//

// CMP
void CMPFunc::execute() {
    if (operands_[0] == operands_[1]){
        (*flags_)[(size_t)ConditionFlags::ZF] = true;
        (*flags_)[(size_t)ConditionFlags::CF] = false;
        (*flags_)[(size_t)ConditionFlags::OF] = false;
    }
    else {
        (*flags_)[(size_t)ConditionFlags::ZF] = false;
        (*flags_)[(size_t)ConditionFlags::ZF] = (operands_[0] < operands_[1]);
        (*flags_)[(size_t)ConditionFlags::ZF] = false;
    }
    //throw std::invalid_argument("empty operand");
}

//=======================================================//

// SHL
void SHLFunc::execute() {
    if (operands_[1] <= 0) {
        throw std::invalid_argument("empty operand");
    }
    operands_[0] = operands_[0] << operands_[1];
}

//=======================================================//

// SHR
void SHRFunc::execute() {
    if (operands_[1] <= 0) {
        throw std::invalid_argument("empty operand");
    }
    operands_[0] = operands_[0] >> operands_[1];
}

//=======================================================//

// JMP 
void JMPFunc::execute() {
    // set pc
}

//=======================================================//

// JE
void JEFunc::execute() {
    if ((*flags_)[(size_t)ConditionFlags::ZF]) {
        // set pc
    }
}

//=======================================================//

// JNE
void JEFunc::execute() {
    if (!(*flags_)[(size_t)ConditionFlags::ZF]) {
        // set pc
    }
}

//=======================================================//

// JG
void JGFunc::execute() {
    if (~(((*flags_)[(size_t)ConditionFlags::SF]) ^ (*flags_)[(size_t)ConditionFlags::OF]) & (~(*flags_)[(size_t)ConditionFlags::ZF])){
        // set pc
    }
}

//=======================================================//

// JGE
void JGEFunc::execute() {
    if (~(((*flags_)[(size_t)ConditionFlags::SF]) ^ (*flags_)[(size_t)ConditionFlags::OF])){
        // set pc
    }
}

//=======================================================//

// JL
void JLFunc::execute() {
    if ((*flags_)[(size_t)ConditionFlags::SF] ^ (*flags_)[(size_t)ConditionFlags::OF]){
        // set pc
    }
}

//=======================================================//

// JLE
void JLEFunc::execute() {
    if (((*flags_)[(size_t)ConditionFlags::SF] ^ (*flags_)[(size_t)ConditionFlags::OF]) | (*flags_)[(size_t)ConditionFlags::ZF]){
        // set pc
    }
}

//=======================================================//

// DB
//=======================================================//

// DW
//=======================================================//

// DD
//=======================================================//