#pragma once

#include <ostream>
#include <cstddef>
#include <utility>
#include <algorithm>
#include "shapes.h"

class Shape2DCollection {
    Shape2D* data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;
};