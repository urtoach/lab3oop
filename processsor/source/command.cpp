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
        operand_->setValue(operand_->getValue() + 1);
        CommandDescriptor::setStat(StatCode::AOK);
    }
    else {
        CommandDescriptor::setStat(StatCode::INS);
    }
}

//=======================================================//

// DEC
void DECFunc::execute() {
    if (UnaryCommand::getOperand()) {
        try { 
            operand_->setValue(operand_->getValue() - 1);
            CommandDescriptor::setStat(StatCode::AOK);
        }
        catch(...) {
            CommandDescriptor::setStat(StatCode::ADR);
        }
    }
    else {
        CommandDescriptor::setStat(StatCode::INS);
    }
}

//=======================================================//

// NOT
void NOTFunc::execute() {
    if (UnaryCommand::getOperand()) {
        try {
            operand_->setValue(~(operand_->getValue()));
            CommandDescriptor::setStat(StatCode::AOK);
        }
        catch(...) {
            CommandDescriptor::setStat(StatCode::ADR);
        }
    }
    else {
        CommandDescriptor::setStat(StatCode::INS);
    }
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
    try {
        operands_[0]->setValue(operands_[0]->getValue() + operands_[1]->getValue());
        CommandDescriptor::setStat(StatCode::AOK);
    }
    catch(...) {
        CommandDescriptor::setStat(StatCode::INS);
    }
}

//=======================================================//

// SUB
void SUBFunc::execute() {
    try {
        operands_[0]->setValue(operands_[0]->getValue() - operands_[1]->getValue());
        CommandDescriptor::setStat(StatCode::AOK);
    }
    catch(...) {
        CommandDescriptor::setStat(StatCode::INS);
    }
}

//=======================================================//

// AND
void ANDFunc::execute() {
    try {
        operands_[0]->setValue(operands_[0]->getValue() & operands_[1]->getValue());
        if (operands_[0] == 0) { (*flags_)[(size_t)ConditionFlags::ZF] = true; }
        else { (*flags_)[(size_t)ConditionFlags::ZF] = false; }
        CommandDescriptor::setStat(StatCode::AOK);
    }
    catch(...) {
        CommandDescriptor::setStat(StatCode::INS);
    }
}

//=======================================================//

// OR
void ORFunc::execute() {
    try {
        operands_[0]->setValue(operands_[0]->getValue() | operands_[1]->getValue());
        if (operands_[0] == 0) { (*flags_)[(size_t)ConditionFlags::ZF] = true; }
        else { (*flags_)[(size_t)ConditionFlags::ZF] = false; }
        CommandDescriptor::setStat(StatCode::AOK);
    }
    catch(...){
        CommandDescriptor::setStat(StatCode::INS);
    }
}

//=======================================================//

// XOR
void XORFunc::execute() {
    try {
        uint64_t op1 = operands_[0]->getValue();
        uint64_t op2 = operands_[1]->getValue();

        operands_[0]->setValue((~op1 & op2) | (~op1 & op2)); 
        if (operands_[0]->getValue() == 0) { 
            (*flags_)[(size_t)ConditionFlags::ZF] = true; 
        }
        else { (*flags_)[(size_t)ConditionFlags::ZF] = false; }
        CommandDescriptor::setStat(StatCode::AOK);
    }
    catch(...){
        CommandDescriptor::setStat(StatCode::INS);
    }
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
    try {
        if (operands_[0]->getValue() == operands_[1]->getValue()){
            (*flags_)[(size_t)ConditionFlags::ZF] = true;
            (*flags_)[(size_t)ConditionFlags::CF] = false;
            (*flags_)[(size_t)ConditionFlags::OF] = false;
        }
        else {
            (*flags_)[(size_t)ConditionFlags::ZF] = false;
            (*flags_)[(size_t)ConditionFlags::ZF] = (operands_[0] < operands_[1]);
            (*flags_)[(size_t)ConditionFlags::ZF] = false;
        }
        CommandDescriptor::setStat(StatCode::AOK);
    }
    catch(...){
        CommandDescriptor::setStat(StatCode::INS);
    }

//=======================================================//

// SHL
void SHLFunc::execute() {
    if (operands_[1]->getValue() <= 0) {
        CommandDescriptor::setStat(StatCode::ADR);
    }
    else {
        operands_[0]->setValue(operands_[0]->getValue() << operands_[1]->getValue());
        CommandDescriptor::setStat(StatCode::AOK);
    }
}

//=======================================================//

// SHR
void SHRFunc::execute() {
    if (operands_[1]->getValue() <= 0) {
        CommandDescriptor::setStat(StatCode::ADR);
    }
    else {
        operands_[0]->setValue(operands_[0]->getValue() >> operands_[1]->getValue());
        CommandDescriptor::setStat(StatCode::AOK);
    }
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