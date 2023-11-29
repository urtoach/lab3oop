#ifndef MEMORY_TYPE_H
#define MEMORY_TYPE_H

#include <iostream>
#include <variant>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <string>
#include <utility>

enum class DataType {
    BYTE = 0, 
    CHAR = 1,
    INT = 2,
    UINT = 3,
    LONG = 4,
    ULONG = 5,
    FLOAT = 6,
    DOUBLE = 7,
    LDOUBLE = 8,
    UNKNOWN
};

using VariantType = std::variant<unsigned char, char, int, unsigned int, long, unsigned long, float, double, long double>;

class Data {
private:
    DataType type_;
    VariantType value_;
    std::vector<uint8_t> bin_value_;

    std::pair<DataType, size_t> getType_() const;

    void initBinary_();
    void updateValue_();

    template<class T>
    void initFromBinary_();

public:
    // constructor
    Data(VariantType value) : value_(value), type_(getType_().first) {};
    Data(DataType type, const std::vector<uint8_t>& bin_value) : type_(type) {};

    // getters
    VariantType getValue() const;
    std::vector<uint8_t> getBinary() const;

    //setter
    void setValue(const VariantType& value);
    void setBinary(DataType type, const std::vector<uint8_t>& bin_value);
};

#endif // MEMORY_TYPE_H