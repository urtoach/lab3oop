#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <functional>

void lexer();
void parser(std::ifstream& file);
void interpritator();
void decoder();

class CommandTable {
private:
    std::unordered_map<std::string, unsigned char> mnemomic_to_opcode_;
public:
    CommandTable();
    unsigned char getOpcode(const std::string& opcode) const;
};

#endif // INTERPRETER_H