#include "../include/Decoder.hpp"
#include <iostream>
#include <fstream>
#include <string>

void decoder(const std::string filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "unable to open file: " << filename << std::endl;
        throw std::runtime_error("unable to open file");
    }
    std::string line;
    while (std::getline(file, line)) {}
    file.close();
}