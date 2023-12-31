#ifndef MEMORY_TYPE_H
#define MEMORY_TYPE_H

#include <iostream>
#include <variant>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <string>
#include <utility>

enum class _Type {
    BYTE = 0, 
    CHAR = 1,
    INT = 2,
    UINT = 3,
    LONG = 4,
    ULONG = 5,
    FLOAT = 6,
    DOUBLE = 7,
    LDOUBLE = 8,
    REGISTER = 9,
    ADDRESS = 10,
    LABEL = 11,
    MNEMONIC = 12,
    UNKNOWN
};

struct DataType {
    _Type type_;
    size_t size_;
};

class TypeTable {
private:
    std::unordered_map<std::type_index, DataType> type_map_;
public:
    TypeTable() {
        type_map_[typeid(char)] = { _Type::BYTE, sizeof(unsigned char) };
        type_map_[typeid(char)] = { _Type::CHAR, sizeof(char) };
        type_map_[typeid(int)] = { _Type::INT, sizeof(int) };
        type_map_[typeid(unsigned int)] = { _Type::UINT, sizeof(unsigned int) };
        type_map_[typeid(long)] = { _Type::LONG, sizeof(long) };
        type_map_[typeid(unsigned long)] = { _Type::ULONG, sizeof(unsigned long) };
        type_map_[typeid(float)] = { _Type::FLOAT, sizeof(float) };
        type_map_[typeid(double)] = { _Type::DOUBLE, sizeof(double) };
        type_map_[typeid(long double)] = { _Type::LDOUBLE, sizeof(long double) };
    }
    DataType getType(VariantType& value) const;

    std::array<size_t, 14> sizeof_{ sizeof(uint8_t), sizeof(char), sizeof(int),
        sizeof(unsigned int), sizeof(long), sizeof(unsigned long), sizeof(float),
        sizeof(double), sizeof(long double), static_cast<size_t>(1), sizeof(size_t), sizeof(size_t), static_cast<size_t>(1), static_cast<size_t>(0) };
};

using VariantType = std::variant<uint8_t, char, int, unsigned int, long, unsigned long, float, double, long double>;

class Data {
private:
    DataType type_;
    VariantType value_;
    std::vector<uint8_t> bin_value_;

    TypeTable table_;

    void initBinary_();
    void updateValue_();

    template<class T>
    void initFromBinary_();

public:
    // constructor
    Data(VariantType value) : value_(value), type_(table_.getType(value)) {};
    Data(DataType type, const std::vector<uint8_t>& bin_value) : type_(type) {};

    // getters
    DataType getType() const { return type_; }
    VariantType getValue() const;
    std::vector<uint8_t> getBinary() const;

    //setter
    void setValue(const VariantType& value);
    void setBinary(DataType type, const std::vector<uint8_t>& bin_value);
};

#endif // MEMORY_TYPE_H