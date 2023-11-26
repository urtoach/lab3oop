
#include <vector>
#include "../include/memorytype.hpp"

// Data
template<class Type>
void Data<Type>::initBinary_() {
    bin_value_.resize(sizeof(Type));
    std::memcpy(bin_value_.data(), &value_, sizeof(Type));
}

template<class Type>
void Data<Type>::udateValue_() {
    if (bin_value_.size() != sizeof(Type)) {
        throw std::runtime_error("invalid memory type");
    }
    std::memcpy(&value_, bin_value_.data(), sizeof(Type));
}

// constructor
template<class Type>
Data<Type>::Data(Type value) : value_(value) {
    initBinary_();
}

// getter
template<class Type>
Type Data<Type>::getValue() const{
    return value_;
}

template<class Type>
std::vector<uint8_t> Data<Type>::getBinary() const {
    return bin_value_;
}

//setter
template<class Type>
void Data<Type>::setValue(const Type& value) {
    value_ = value;
    initBinary_();
}

template<class Type>
void Data<Type>::setBinary(const std::vector<uint8_t>& bin_value){
    if (bin_value_.size() != sizeof(Type)) {
        throw std::runtime_error("invalid memory type");
    }
    bin_value_ = bin_value;
    updateValue_();
}





