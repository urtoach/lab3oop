#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <memory>

template<class T>
class MyVector {
private:
    Type *vector_;
    size_t size_;
    size_t capacity_;
public:
    // constructor
    MyVector() : vector_(nullptr), size_(0), capacity_(0) {}
    MyVector(size_t size) : size_(size), capacity_(size), vector_(new T[size]);

    // destructor
    ~MyVector();

    // copy constructor
    MyVector(const MyVector<T> &other) : vector_(new T[other.size_]), size_(other.size_), capacity_(other.size_);

    MyVector<T> &operator=(const MyVector<T> &other);

    // getter
    size_t size() const;
    size_t capacity() const;

    // methods
    void reserve_(size_t new_capacity);
    void resize(size_t new_size);
    T &operator[](size_t indx);
    void push_back(const T &value);
    void pop_back();
};

#endif // MYVECTOR_H