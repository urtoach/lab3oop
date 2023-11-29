
#include <vector>
#include "../include/memorytype.hpp"
#include <cstdint>
#include <cstring>

// Data
Data::Data(DataType type, const std::vector<uint8_t>& bin_value) : type_(type) {
    bin_value_ = bin_value;
    updateValue_();
}

void Data::initBinary_() {
    bin_value_.resize(getType_().second);
    std::memcpy(bin_value_.data(), &value_, getType_().second);
}

template<class T>
void Data::initFromBinary_() {
    if (bin_value_.size() != sizeof(T)) {
        throw std::runtime_error("invalid memory type");
    }
    std::memcpy(&value_, bin_value_.data(), sizeof(T));
} 

std::pair<DataType, size_t> Data::getType_() const {
    static std::unordered_map<std::type_index, std::pair<DataType, size_t>> type_map {
        { typeid(char), {DataType::CHAR, sizeof(char)} },
        { typeid(int), {DataType::INT, sizeof(int)} },
        { typeid(unsigned int), {DataType::UINT, sizeof(unsigned int)} },
        { typeid(long), {DataType::LONG, sizeof(long)} },
        { typeid(unsigned long), {DataType::ULONG, sizeof(unsigned long)} },
        { typeid(float), {DataType::FLOAT, sizeof(float)} },
        { typeid(double), {DataType::DOUBLE, sizeof(double)} },
        { typeid(long double), {DataType::LDOUBLE, sizeof(long double)} }
    };

    const std::type_index type = typeid(value_);
    auto it = type_map.find(type);
    return (it != type_map.end()) ? it->second : std::pair{ DataType::UNKNOWN, size_t(0) };
}


void Data::updateValue_() {
    switch(getType_().first){
        case DataType::BYTE: {
            initFromBinary_<uint8_t>();
            break;
        }
        default: { break; }
    }
}

// constructor
Data::Data(VariantType value) : value_(value), type_(getType_().first) {
    initBinary_();
}

// getter
VariantType Data::getValue() const{
    return value_;
}

std::vector<uint8_t> Data::getBinary() const {
    return bin_value_;
}

//setter
void Data::setValue(const VariantType& value) {
    value_ = value;
    type_ = getType_().first;
    initBinary_();
}

void Data::setBinary(DataType type, const std::vector<uint8_t>& bin_value){
    if (bin_value_.size() != getType_().second) {
        throw std::runtime_error("invalid memory type");
    }
    bin_value_ = bin_value;
    updateValue_();
}





