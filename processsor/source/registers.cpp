#include "../include/registers.hpp"
#include <iostream>
#include <array>


// Register
// getters
GPRegister Register::getName() const {
    return name_;
}

uint64_t Register::getValue() const {
    return value_;
}

bool Register::isLocked() const {
    return lock_;
}

// setters
void Register::setName(const GPRegister name) {
    name_ = name;
}

void Register::setValue(const uint64_t value) {
    value_ = value;
}

// other methods
void Register::locking() {
    lock_ = !lock_;
}

//======================================================//

// RegisterBlock
// constructors
RegisterBlock::RegisterBlock() {
        for (size_t i = 0; i < NUMBER_OF_GPR; i++){
            registers_[i] = Register(static_cast<GPRegister>(i));
        }
    }

RegisterBlock::RegisterBlock(std::array<uint64_t, NUMBER_OF_GPR>& values) {
    // Инициализация значений регистров
    for (size_t i = 0; i < NUMBER_OF_GPR; ++i) {
        registers_[i] = Register(static_cast<GPRegister>(i), values[i]);
    }
}

// getters
std::array<Register, NUMBER_OF_GPR> RegisterBlock::getRegisters(GPRegister name) const {
    return registers_;
}

// setters
void RegisterBlock::setRegisters(const std::array<Register, NUMBER_OF_GPR>& registers) {
    registers_ = registers;
}

// other methods
void RegisterBlock::lockRegister(GPRegister name) {
    registers_[static_cast<size_t>(name)].locking();
}

void RegisterBlock::lockAll() {
    for (size_t i = 0; i < NUMBER_OF_GPR; ++i) {
        registers_[i].locking();
    }
}
//======================================================//