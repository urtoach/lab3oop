#define DECODER_H
#ifndef DECODER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class CodeTable {
private:
    std::unordered_map<unsigned char, CommandCreator> opcode_to_comm
public:
};

#endif //DECODER_H