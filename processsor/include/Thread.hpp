#define THREAD_H
#ifndef THREAD_H

#include <string>
#include <Registers.hpp>

class Thread {
private:
    std::string id;
    Register programCounter;
public:
};

#endif //THREAD_H
