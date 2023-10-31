#ifndef EXECUTIONDEVICE_H
#define EXECUTIONDEVICE_H

#include "Command.h"
#include <string>

class ExecutionDevice {
private:
    std::string name_;
    int executionTime_;
    bool available_;
public:
    ExecutionDevice(const std::string& name, int executionTime);
    void ExecuteCommand(const Command& command);

    const std::string& GetName() const;
    int GetExecutionTime() const;
    bool IsAvailable() const;
    void SetAvailable(bool available);
};

#endif // EXECUTIONDEVICE_H