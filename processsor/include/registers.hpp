#ifndef REGISTER
#define REGISTER_H

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
    // constructors
    Register();
    Register(GPRegister name) : name_(name) {};
    Register(GPRegister name, uint64_t value) : name_(name), value_(value) {};
    Register(GPRegister name, uint64_t value, bool lock) : name_(name), value_(value), lock_(lock) {};

    // destructors
    ~Register();

    // getters
    GPRegister getName() const;
    uint64_t getValue() const;
    bool isLocked() const;

    // setters
    void setName(const GPRegister name);
    void setValue(const uint64_t value);

    // other methods
    void locking();
};

class RegisterBlock {
private:
    std::array<Register, NUMBER_OF_GPR> registers_;
public:
    // constructors
    RegisterBlock();
    RegisterBlock(std::array<uint64_t, NUMBER_OF_GPR>& values);

    // destructors
    ~RegisterBlock();

    // getters
    std::array<Register, NUMBER_OF_GPR> getRegisters(GPRegister name) const;

    // setters
    void setRegisters(const std::array<Register, NUMBER_OF_GPR>& registers);

    // other methods
    void lockRegister(GPRegister name);
    void lockAll();
};



#endif //REGISTER_H