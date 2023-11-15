#define THREAD_H
#ifndef THREAD_H

#include <string>
#include <Registers.hpp>

class Thread {
private:
    std::string id;
    Register programCounter;
public:
    void execute();
    Register getPC() const;
    void setPC(const Register &pc);
};

#endif //THREAD_H