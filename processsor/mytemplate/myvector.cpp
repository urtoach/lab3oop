#include "myvector.hpp"


// constructor
template<class T>
MyVector<T>::MyVector(size_t size) : vector_(new T[size]), size_(size), capacity_(size) {

}
//=============================================================//

// destructor
template<class T>
MyVector<T>::~MyVector() { 
    delete[] vector_;
    size_ = 0;
    capacity_ = 0;
}
//=============================================================//

// copy constructor
template<class T>
MyVector<T>::MyVector(const MyVector<T> &other) : vector_(new T[other.size_]), size_(other.size_), capacity_(other.size_) {
    for (size_t i = 0; i < size_; i++) {
        vector_[i] = other.vector_[i];
    }
}
//=============================================================//
    
// getter
template<class T>
size_t MyVector<T>::size() const { 
    return size_;
}

template<class T>
size_t MyVector<T>::capacity() const {
    return capacity_;
}
//=============================================================//

// methods
template<class T>
MyVector<T> &MyVector<T>::operator=(const MyVector<T> &other) {
    if (this != &other) {
        delete[] vector_;
        size_ = other.size_;
        capacity_ = other.size_;
        vector_ = new T[size_];
        for (size_t i = 0; i < size_; i++) {
            vector_[i] = other.vector_[i];
        }
    }
    return *this;
}

//=============================================================//

template<class T>
void MyVector<T>::reserve_(size_t new_capacity) {
    if (new_capacity > capacity_) {
        T *temp = new T[new_capacity];
        for (size_t i = 0; i < size_; i++) {
            temp[i] = vector_[i];
        }
        delete[] vector_;
        vector_ = temp;
        capacity_ = new_capacity;
    }
}

//=============================================================//

template<class T>
void MyVector<T>::resize(size_t new_size) {
    if (new_size > capacity_) {
        reserve(new_size);
    }
    if (new_size > size_) {
        for (size_t i = size_; i < new_size; ++i) {
            vector_[i] = T();
        }
    }
    size_ = new_size;
}

//=============================================================//

template<class T>
T &MyVector<T>::operator[](size_t indx) {
    if (indx >= size_) {
        throw std::invalid_argument("invalid index");
    }
    return vector_[index];
}

//=============================================================//

template<class T>
void MyVector<T>::push_back(const T &value) {
    if (size_ >= capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    vector_[size_] = value;
    size_++;
}

//=============================================================//

template<class T>
void MyVector<T>::pop_back() {
    if (size_ > 0) {
        size_--;
    }
}

//=============================================================//