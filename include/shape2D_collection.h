#pragma once

#include <ostream>
#include <cstddef>
#include <utility>
#include <algorithm>
#include <vector>
#include "shapes.h"

class Shape2DCollection {
    Shape2D** data_;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;
    void clear_data();
    void swap(Shape2DCollection&);
public:
    Shape2DCollection();
    Shape2DCollection(const Shape2DCollection&);
    Shape2DCollection(Shape2DCollection&&);
    Shape2DCollection& operator=(Shape2DCollection);
    ~Shape2DCollection();
    std::size_t size() const;
    bool add(Shape2D&);
    bool remove(Shape2D&);
    const Shape2D& operator[](std::size_t) const;
    Shape2D& operator[](std::size_t);
    double metric();
    operator double();
};