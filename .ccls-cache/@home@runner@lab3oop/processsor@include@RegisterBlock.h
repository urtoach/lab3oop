#ifndef REGISTERBLOCK_H
#define REGISTERBLOCK_H

#include <vector>

class RegisterBlock {
private:
    std::vector<int> registers;
    std::vector<bool> registerLocks;
public:
    RegisterBlock(int numRegisters);
    int getRegisterValue(int registerIndex);
    void setRegisterValue(int registerIndex, int value);
    bool isRegisterLocked(int registerIndex);
    void setRegisterLock(int registerIndex, bool locked);
};

#endif // REGISTERBLOCK_H