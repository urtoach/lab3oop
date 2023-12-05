#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include <cstring>
#include <unordered_map>
#include "../include/interpreter.hpp"
#include "../include/processor.hpp"


// Label Map
//==================================================//
void LabelMap::pushLabel(const std::string& label, size_t address) {
    labels_[label] = address;
}

size_t LabelMap::getAddress(const std::string& label) {
    auto it = labels_.find(label);
    if (it != labels_.end()) { return it->second; } 
    else { return 0; }
}

//==================================================//


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
        return { TokenType::LABEL, token.substr(0, token.size() - 1) };
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
    if (labels.getAddress(token) != 0) {
        return { TokenType::LABEL, token };
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
void Parser::processToken_(const Token& token, ProgramMemory& program, DataMemory& data) {
    std::vector<uint8_t> binary;
    switch(token.type) {
        case TokenType::ADDRESS:{
            int value = std::atoi(token.name.c_str());
            binary.resize(sizeof(int));
            std::memcpy(binary.data(), &value, sizeof(int));
            binary.insert(binary.begin(), static_cast<uint8_t>(_Type::ADDRESS));
            break;
        }
        case TokenType::MNEMONIC:{
            uint8_t opcode = getOpcode_(token.name);
            if (opcode == 0xFF){
                throw;
            }
            binary.push_back(opcode);
            binary.insert(binary.begin(), static_cast<uint8_t>(_Type::MNEMONIC));
            break;
        }
        case TokenType::REGISTER:{
            uint8_t rcode = getOpcode_(token.name);
            if (rcode == 0xFF){
                throw;
            }
            binary.push_back(rcode);
            binary.insert(binary.begin(), static_cast<uint8_t>(_Type::REGISTER));
            break;
        }
        case TokenType::NUMBER:{
            if (lexer_.isInt_(token.name)){
                int value = std::stoi(token.name.c_str());
                binary.resize(sizeof(int));
                std::memcpy(binary.data(), &value, sizeof(int));
                binary.insert(binary.begin(), static_cast<uint8_t>(_Type::INT));
            }
            else {
                double value = std::stod(token.name.c_str());
                binary.resize(sizeof(double));
                std::memcpy(binary.data(), &value, sizeof(double));
                binary.insert(binary.begin(), static_cast<uint8_t>(_Type::DOUBLE));
            }
            break;
        }
        case TokenType::LABEL:{
            size_t address = lexer_.labels.getAddress(token.name);
            if (address == 0) { 
                address = program.getSize();
                lexer_.labels.pushLabel(token.name, address);
                binary.resize(sizeof(size_t));
                binary.insert(binary.begin(), static_cast<uint8_t>(_Type::LABEL));
            }
            else {
                binary.resize(sizeof(size_t));
                std::memcpy(binary.data(), &address, sizeof(size_t));
                binary.insert(binary.begin(), static_cast<uint8_t>(_Type::LABEL));
            }
            break;
        }
        case TokenType::COMMENT:{
            break;
        }
        case TokenType::END:{
            uint8_t opcode = getOpcode_("hlt");
            binary.push_back(opcode);
            break;
        }
        case TokenType::UNKNOWN:{
            throw;
        }
    }
    program.write(binary);
}

void Parser::parse(ProgramMemory& program, DataMemory& data) {
    Token token;
    do {
        token = lexer_.getNext();
        processToken_(token, program, data);
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

    opcode_table_["%rax"] = 0;
    opcode_table_["%rbx"] = 1;
    opcode_table_["%rcx"] = 2;
    opcode_table_["%rdx"] = 3;
    opcode_table_["%rsp"] = 4;
    opcode_table_["%rbp"] = 5;
    opcode_table_["%rsi"] = 6;
    opcode_table_["%rdi"] = 7;
    opcode_table_["%r8"] = 8;
    opcode_table_["%r9"] = 9;
    opcode_table_["%r10"] = 10;
    opcode_table_["%r11"] = 11;
    opcode_table_["%r12"] = 12;
    opcode_table_["%r13"] = 13;
    opcode_table_["%r14"] = 14;
}

uint8_t Parser::getOpcode_(const std::string& mnemonic) {
    if (opcode_table_.find(mnemonic) != opcode_table_.end()) {
            return opcode_table_.at(mnemonic);
        }
    return 0xFF;
}

