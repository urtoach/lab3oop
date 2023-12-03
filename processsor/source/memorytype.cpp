
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
    bin_value_.resize(type_.size_);
    std::memcpy(bin_value_.data(), &value_, type_.size_);
}

template<class T>
void Data::initFromBinary_() {
    if (bin_value_.size() != sizeof(T)) {
        throw std::runtime_error("invalid memory type");
    }
    std::memcpy(&value_, bin_value_.data(), sizeof(T));
} 

DataType TypeTable::getType(VariantType& value) const {
    const std::type_index type = typeid(value);
    auto it = type_map_.find(type);
    return (it != type_map_.end()) ? it->second : DataType{ _Type::UNKNOWN, static_cast<size_t>(0) };
}


void Data::updateValue_() {
    switch(type_.type_){
        case _Type::BYTE: {
            initFromBinary_<uint8_t>();
            break;
        }
        case _Type::CHAR: {
            initFromBinary_<char>();
            break;
        }
        case _Type::INT: {
            initFromBinary_<int>();
            break;
        }
        case _Type::UINT: {
            initFromBinary_<unsigned int>();
            break;
        }
        case _Type::LONG: {
            initFromBinary_<long>();
            break;
        }
        case _Type::FLOAT: {
            initFromBinary_<float>();
            break;
        }
        case _Type::DOUBLE: {
            initFromBinary_<double>();
            break;
        }
        case _Type::LDOUBLE: {
            initFromBinary_<long double>();
            break;
        }
        case _Type::ULONG: {
            initFromBinary_<unsigned long>();
            break;
        }
        default: { 
            throw std::runtime_error("invalid memory type");
        }
    }
}

// constructor
Data::Data(VariantType value) : value_(value), type_(table_.getType(value)) {
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
    type_ = table_.getType(value_);
    initBinary_();
}

void Data::setBinary(DataType type, const std::vector<uint8_t>& bin_value){
    if (bin_value_.size() != type.size_) {
        throw std::runtime_error("invalid memory type");
    }
    type_ = type;
    bin_value_ = bin_value;
    updateValue_();
}





