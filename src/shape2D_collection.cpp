#include "../include/shape2D_collection.h"

Shape2DCollection::Shape2DCollection(): data_(nullptr), size_(0), capacity_(0) {}

Shape2DCollection::Shape2DCollection(const Shape2DCollection& other) {
    if (data_ == other.data_ && size_ == other.size_ && capacity_ == other.capacity_) {
        return;
    }
    Shape2D** new_data = new Shape2D*[other.capacity_];
    for (std::size_t i{}; i < other.size_; ++i) {
        new_data[i] = new Shape2D(*other.data_[i]);
    }

    clear_data();

    data_ = new_data;
    size_ = other.size_;
    capacity_ = other.capacity_;
}

 void Shape2DCollection::clear_data() {
    for (std::size_t i{}; i < size_; ++i) {
        delete data_[i];
    }
    delete[] data_;
}

Shape2DCollection::Shape2DCollection(Shape2DCollection&& other) {
    if (data_ == other.data_ && size_ == other.size_ && capacity_ == other.capacity_) {
        return;
    }
    clear_data();
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.data_ = nullptr;
    other.capacity_ = 0;
    other.size_ = 0;
}

void Shape2DCollection::swap(Shape2DCollection& other) noexcept {
    std::swap(other.data_, data_);
    std::swap(other.size_, size_);
    std::swap(other.capacity_, capacity_);
}

Shape2DCollection& Shape2DCollection::operator=(Shape2DCollection other) {
    if (data_ == other.data_ && size_ == other.size_ && capacity_ == other.capacity_) {
        return;
    }
    swap(other);
    return *this;
}

Shape2D& Shape2DCollection::operator[](std::size_t i) {
    if (i > size_ - 1) {
        throw std::out_of_range("index out of Shape2DCollection size");
    }
    return *data_[i];
}

const Shape2D& Shape2DCollection::operator[](std::size_t i) const {
    if (i > size_ - 1) {
        throw std::out_of_range("index out of Shape2DCollection size");
    }
    return *data_[i];
}

std::size_t Shape2DCollection::size() const {
    return size_;
}

bool Shape2DCollection::add(Shape2D& s) {
    if (size_ == capacity_) {
        if (capacity_ == 0) { capacity_++; }
        capacity_ *= 2;
        Shape2D** new_data_ = new Shape2D*[capacity_];
        for (std::size_t i{}; i < size_; ++i) {
            new_data_[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data_;
    }
    Shape2D* new_s = new Shape2D(s);
    data_[size_] = new_s;
    ++size_;
    return true;
}

bool Shape2DCollection::remove(Shape2D& s) {
    for (std::size_t i{}; i < size_; ++i) {
        if (*data_[i] == s) {
            Shape2D* sav = data_[i];
            for (std::size_t j{i}; j < size_ - 1; ++j) {
                data_[j] = data_[j+1];
            }
            delete sav;
            return true;
        }
    }
    return false;
}

double Shape2DCollection::metric() {
    double cumul_metric = 0;
    for (std::size_t i{}; i < size_; ++i) {
        cumul_metric += (double)(*data_[i]);
    }
    return cumul_metric;
}

Shape2DCollection::operator double() {
    return metric();
}