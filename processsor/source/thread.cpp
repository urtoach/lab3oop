#include "../include/thread.hpp"

Thread::Thread(std::string& id) : id_(id), program_counter_(Register(GPRegister::rip)) {}

Thread::Thread(std::string& id, const Register& pc) : id_(id), program_counter_(pc) {}

Thread::~Thread() {}

std::string Thread::getId() const {
    return id_;
}

Register Thread::getPC() const {
    return program_counter_;
}

void Thread::setId(const std::string& id) {
    id_ = id;
}

void Thread::setPC(const Register pc) {
    program_counter_ = pc;
}

void Thread::execute() {

    program_counter_.setValue(program_counter_.getValue() + 1);
}