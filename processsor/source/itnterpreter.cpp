#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include <unordered_map>
#include "../include/interpreter.hpp"
#include "../include/processor.hpp"


// Lexer
//==================================================//
// construcor
explicit Lexer::Lexer(const std::string& filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::invalid_argument("invalid filename");
    }

    std::string line; 
    while (std::getline(file, line)) {
        tokenizeLine(line);
    }
    tokens_.push_back({ TokenType::END, "" });
    file.close();
    createTable_();
}

void Lexer::createTable_() {
    token_type_table_["mov"] = TokenType::MNEMONIC;

    token_type_table_["add"] = TokenType::MNEMONIC;
    token_type_table_["sub"] = TokenType::MNEMONIC;
    token_type_table_["inc"] = TokenType::MNEMONIC;
    token_type_table_["dec"] = TokenType::MNEMONIC;

    token_type_table_["not"] = TokenType::MNEMONIC;
    token_type_table_["and"] = TokenType::MNEMONIC;
    token_type_table_["or"] = TokenType::MNEMONIC;
    token_type_table_["xpr"] = TokenType::MNEMONIC;
    token_type_table_["cmp"] = TokenType::MNEMONIC;

    token_type_table_["shl"] = TokenType::MNEMONIC;
    token_type_table_["shr"] = TokenType::MNEMONIC;

    token_type_table_["jmp"] = TokenType::MNEMONIC;
    token_type_table_["je"] = TokenType::MNEMONIC;
    token_type_table_["jne"] = TokenType::MNEMONIC;
    token_type_table_["jg"] = TokenType::MNEMONIC;
    token_type_table_["jge"] = TokenType::MNEMONIC;
    token_type_table_["jl"] = TokenType::MNEMONIC;
    token_type_table_["jle"] = TokenType::MNEMONIC;

    token_type_table_["db"] = TokenType::MNEMONIC;
    token_type_table_["dw"] = TokenType::MNEMONIC;
    token_type_table_["dd"] = TokenType::MNEMONIC;

    token_type_table_["hlt"] = TokenType::MNEMONIC;

    token_type_table_["%rax"] = TokenType::REGISTER;
    token_type_table_["%rbx"] = TokenType::REGISTER;
    token_type_table_["%rcx"] = TokenType::REGISTER;
    token_type_table_["%rdx"] = TokenType::REGISTER;
    token_type_table_["%rsp"] = TokenType::REGISTER;
    token_type_table_["%rbp"] = TokenType::REGISTER;
    token_type_table_["%rsi"] = TokenType::REGISTER;
    token_type_table_["%rdi"] = TokenType::REGISTER;
    token_type_table_["%r8"] = TokenType::REGISTER;
    token_type_table_["%r9"] = TokenType::REGISTER;
    token_type_table_["%r10"] = TokenType::REGISTER;
    token_type_table_["%r11"] = TokenType::REGISTER;
    token_type_table_["%r12"] = TokenType::REGISTER;
    token_type_table_["%r13"] = TokenType::REGISTER;
    token_type_table_["%r14"] = TokenType::REGISTER;
}

TokenType Lexer::getTokenType_(const std::string& token) const {
    if (token_type_table_.find(token) != token_type_table_.end()) {
            return token_type_table_.at(token);
        }
    return TokenType::UNKNOWN;
}

Token Lexer::getNext() {
    if (current_pos_ < tokens_.size()) {
        return tokens_[current_pos_++];
    }
    return { TokenType::END, "" };
}

bool Lexer::isInt_(const std::string& num) {
    return !num.empty() && num.find_first_not_of("0123456789") == std::string::npos;
}

bool Lexer::isDouble_(const std::string& num) {
    char* endptr = nullptr;
    strtod(num.c_str(), &endptr);
    return !num.empty() && *endptr == '\0';
}

Token Lexer::createToken_(const std::string& token) {
    if (token.front() == ';') {
        return { TokenType::COMMENT, token };
    }
    if (token.back() == ':') {
        return { TokenType::LABEL, token };
    }
    if (token.front() == '[' && token.back() == ']'){
        std::string address = token.substr(1, token.size() - 2);
        if (isInt_(address)) {
            return { TokenType::ADDRESS, address };
        }
    }
    if (isDouble_(token)){
        return { TokenType::NUMBER, token };
    }
    return { getTokenType_(token), token };
}

void Lexer::tokenizeLine(const std::string& line) {
    std::istringstream iss(line);
    std::string token;
    while(iss >> token) {
        tokens_.push_back(createToken_(token));
    }
}

//==================================================//

// Parser
//==================================================//

// utility methods
void Parser::processToken_(const Token& token) {
    switch(token.type) {
        case TokenType::ADDRESS:{}
        case TokenType::MNEMONIC:{}
        case TokenType::REGISTER:{}
        case TokenType::NUMBER:{}
        case TokenType::LABEL:{}
        case TokenType::COMMENT:{}
        case TokenType::END:{}
        case TokenType::UNKNOWN:{}
    }
}

void Parser::parse(ProgramMemory& program, DataMemory& data) {
    Token token;
    do {
        token = lexer_.getNext();
        processToken_(token);
    } while((token.type != TokenType::UNKNOWN) || (token.type != TokenType::END));
}

void Parser::createTable_() {
    opcode_table_["mov"] = 0x00;

    opcode_table_["add"] = 0x01;
    opcode_table_["sub"] = 0x02;
    opcode_table_["inc"] = 0x03;
    opcode_table_["dec"] = 0x04;

    opcode_table_["not"] = 0x05;
    opcode_table_["and"] = 0x06;
    opcode_table_["or"] = 0x07;
    opcode_table_["xpr"] = 0x08;
    opcode_table_["cmp"] = 0x09;

    opcode_table_["shl"] = 0x0A;
    opcode_table_["shr"] = 0x0B;

    opcode_table_["jmp"] = 0x0C;
    opcode_table_["je"] = 0x0D;
    opcode_table_["jne"] = 0x0E;
    opcode_table_["jg"] = 0x0F;
    opcode_table_["jge"] = 0x10;
    opcode_table_["jl"] = 0x11;
    opcode_table_["jle"] = 0x12;

    opcode_table_["db"] = 0x13;
    opcode_table_["dw"] = 0x14;
    opcode_table_["dd"] = 0x15;

    opcode_table_["hlt"] = 0x16;
}

uint8_t Parser::getOpcode_(const std::string& mnemonic) {
    if (opcode_table_.find(mnemonic) != opcode_table_.end()) {
            return opcode_table_.at(mnemonic);
        }
    return 0xFF;
}

