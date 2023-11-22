#ifndef THREAD_H
#define THREAD_H

#include <string>
#include <registers.hpp>

class Thread {
private:
    std::string id_;
    Register program_counter_;
public:
    // constructor
    Thread(std::string& id);
    Thread(std::string& id, const Register& pc);

    // destructor
    ~Thread();
    
    // getters
    std::string& getId() const;
    Register getPC() const;

    // setters
    void setId(const std::string& id);
    void setPC(const Register pc);
    
    //other methods
    void execute();
};

#endif //THREAD_H