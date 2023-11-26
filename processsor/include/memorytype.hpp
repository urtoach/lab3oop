#ifndef MEMORY_TYPE_H
#define MEMORY_TYPE_H

#include <iostream>

template<class Type>
class Data {
private:
    Type value_;
    std::vector<uint8_t> bin_value_;

    void initBinary_();
    void udateValue_();
public:
    // constructor
    Data(Type value) : value_(value);

    // getters
    Type getValue() const;
    std::vector<uint8_t> getBinary() const;

    //setter
    void setValue(const Type& value);
    void setBinary(const std::vector<uint8_t>& bin_value);
};

#endif // MEMORY_TYPE_H