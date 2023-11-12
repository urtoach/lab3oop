#ifndef OPERAND_H
#define OPERAND_H

#include <string>

class Operand {
private:
    std::string identifier;
    int value;
public:
    Operand(const std::string& id, int value);
    std::string getIdentifier() const;
    int getValue() const;
    void setValue(int value);
};

#endif // OPERAND_H