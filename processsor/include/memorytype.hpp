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

class TypeTable {
private:
    std::array<size_t, 10> sizeof_;
public:
    TypeTable() {
        sizeof_[static_cast<size_t>(DataType::BYTE)] = sizeof(unsigned char);
        sizeof_[static_cast<size_t>(DataType::CHAR)] = sizeof(char);
        sizeof_[static_cast<size_t>(DataType::INT)] = sizeof(int);
        sizeof_[static_cast<size_t>(DataType::UINT)] = sizeof(unsigned int);
        sizeof_[static_cast<size_t>(DataType::LONG)] = sizeof(long);
        sizeof_[static_cast<size_t>(DataType::ULONG)] = sizeof(unsigned long);
        sizeof_[static_cast<size_t>(DataType::FLOAT)] = sizeof(float);
        sizeof_[static_cast<size_t>(DataType::DOUBLE)] = sizeof(double);
        sizeof_[static_cast<size_t>(DataType::LDOUBLE)] = sizeof(long double);
        sizeof_[static_cast<size_t>(DataType::UNKNOWN)] = 0;
    }
    size_t getSize(DataType type) const {
        return sizeof_[static_cast<size_t>(type)];
    }
};



using VariantType = std::variant<unsigned char, char, int, unsigned int, long, unsigned long, float, double, long double>;

class Data {
    friend TypeTable;
private:
    DataType type_;
    VariantType value_;
    std::vector<uint8_t> bin_value_;

    void initBinary_();
    void updateValue_();

    template<class T>
    void initFromBinary_();

public:
    // constructor
    Data(VariantType value) : value_(value), type_(getType_()) {};
    Data(DataType type, const std::vector<uint8_t>& bin_value) : type_(type) {};

    // getters
    DataType getType() const;
    VariantType getValue() const;
    std::vector<uint8_t> getBinary() const;

    //setter
    void setValue(const VariantType& value);
    void setBinary(DataType type, const std::vector<uint8_t>& bin_value);
};

#endif // MEMORY_TYPE_H