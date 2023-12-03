#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <functional>

#include "memory.hpp"
#include "memorytype.hpp"

// token type for lexer
enum class TokenType {
    MNEMONIC,
    REGISTER,
    ADDRESS,
    NUMBER,
    LABEL,
    COMMENT,
    END,
    UNKNOWN
};

// token
struct Token {
    TokenType type;
    std::string name;
};

// class lexer
class Lexer {
private:
    std::vector<Token> tokens_;
    size_t current_pos_;
    std::unordered_map<std::string, TokenType> token_type_table_;

    // utility methods
    void createTable_();

    bool isInt_(const std::string& num);
    bool isDouble_(const std::string& num);

    TokenType getTokenType_(const std::string& token) const;
    void tokenizeLine(const std::string& line);
    Token createToken_(const std::string& token);
public:
    // constructor
    explicit Lexer(const std::string& filename);
    // getter
    Token getNext();
};

// class Parser
class Parser {
private:
    Lexer lexer_;
    void processToken_(const Token& token);

    std::unordered_map<std::string, uint8_t> opcode_table_;
    // table methods
    void createTable_();
    uint8_t getOpcode_(const std::string& mnemonic);
public:

    explicit Parser(const std::string& filename) : lexer_(filename) {}
    void parse(ProgramMemory& program, DataMemory& data);
};

#endif // INTERPRETER_H