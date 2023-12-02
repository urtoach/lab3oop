
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
    TypeTable table;
    bin_value_.resize(table.getSize(getType_()));
    std::memcpy(bin_value_.data(), &value_, table.getSize(getType_()));
}

template<class T>
void Data::initFromBinary_() {
    if (bin_value_.size() != sizeof(T)) {
        throw std::runtime_error("invalid memory type");
    }
    std::memcpy(&value_, bin_value_.data(), sizeof(T));
} 

DataType Data::getType() const {
    static std::unordered_map<std::type_index, DataType> type_map {
        { typeid(char), DataType::CHAR },
        { typeid(int), DataType::INT },
        { typeid(unsigned int), DataType::UINT },
        { typeid(long), DataType::LONG },
        { typeid(unsigned long), DataType::ULONG },
        { typeid(float), DataType::FLOAT },
        { typeid(double), DataType::DOUBLE },
        { typeid(long double), DataType::LDOUBLE }
    };

    const std::type_index type = typeid(value_);
    auto it = type_map.find(type);
    return (it != type_map.end()) ? it->second : DataType::UNKNOWN;
}


void Data::updateValue_() {
    switch(getType_()){
        case DataType::BYTE: {
            initFromBinary_<uint8_t>();
            break;
        }
        default: { break; }
    }
}

// constructor
Data::Data(VariantType value) : value_(value), type_(getType_()) {
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
    type_ = getType_();
    initBinary_();
}

void Data::setBinary(DataType type, const std::vector<uint8_t>& bin_value){
    TypeTable table;
    if (bin_value_.size() != table.getSize(getType_())) {
        throw std::runtime_error("invalid memory type");
    }
    bin_value_ = bin_value;
    updateValue_();
}





