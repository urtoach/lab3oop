#define REGISTER_H
#ifndef REGISTER_H

// number of general purpose registers
constexpr int NUMBER_OF_GPR = 16;

// general purpose registers in 64-bit
enum class GPRegister {
    rax,
    rbx,
    rcx,
    rdx,
    rsp,
    rbp,
    rsi,
    rdi,
    r8,
    r9,
    r10,
    r11,
    r12,
    r13,
    r14,
    r15
};

enum class ConditionFlags {
    ZF, // zero
    CF, // carry
    SF, // sign
    OF // overflow
};

enum class StatCode {
    AOK, // success
    HLT, // halt
    ADR, // invalid adress
    INS // invalid instruction
};

class Register {
private:
    GPRegister name_;
    uint64_t value_;
    bool lock_;
public:
    GPRegister getName() const;
    bool isLocked() const;

    void locking();
};

class RegisterBlock {
private:
    std::array<Register, NUMBER_OF_GPR> registers_;
public:
    Register& getRegister(GPRegister name);
    void lockRegister(GPRegister name);
    void lockAll();
};



#endif //REGISTER_H