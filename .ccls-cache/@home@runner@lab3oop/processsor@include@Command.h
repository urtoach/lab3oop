#ifndef COMMAND_H
#define COMMAND_H

#include "Functor.h"
#include "Operand.h"

class Command {
private:
    std::string label;
    Functor* operation;
public:
    Command(const std::string& label, Functor* operation);
    virtual void execute() = 0;
    virtual std::string getLabel() const;
};

class UnaryCommand : public Command {
private:
    Operand* operand;
public:
    UnaryCommand(const std::string& label, Functor* operation, Operand* operand);
    void execute() override;
};

class BinaryCommand : public Command {
private:
    Operand* operand1;
    Operand* operand2;
public:
    BinaryCommand(const std::string& label, Functor* operation, Operand* operand1, Operand* operand2);
    void execute() override;
};

class JumpCommand : public Command {
private:
    std::string jumpLabel;
public:
    JumpCommand(const std::string& label, Functor* operation, const std::string& jumpLabel);
    void execute() override;
};

class DataDeclarationCommand : public Command {
private:
    std::string dataLabel;
    int value;
public:
    DataDeclarationCommand(const std::string& label, Functor* operation, const std::string& dataLabel, int value);
    void execute() override;
};

class ThreadInitializationCommand : public Command {
private:
    std::string jumpLabel;
public:
    ThreadInitializationCommand(const std::string& label, Functor* operation, const std::string& jumpLabel);
    void execute() override;
};

class ThreadCompletionCommand : public Command {
public:
    ThreadCompletionCommand(const std::string& label, Functor* operation);
    void execute() override;
};

#endif // COMMAND_H