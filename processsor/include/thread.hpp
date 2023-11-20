#define THREAD_H
#ifndef THREAD_H

#include <string>
#include <registers.hpp>

class Thread {
private:
    std::string id_;
    Register program_counter_;
public:
    void execute();
    Register getPC() const;
    void setPC(const Register &pc);
};

#endif //THREAD_H