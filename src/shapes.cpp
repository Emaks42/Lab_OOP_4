#include "../include/shapes.h"

std::ostream& operator<<(std::ostream& os, Shape2D s) {
    s.print(os);
    return os;
}

std::istream& operator>>(std::istream& is_, Shape2D s) {
    s.read(is_);
    return is_;
}

Shape2D::operator double() const {
    return metric();
}

bool Shape2D::operator==(const Shape2D& other) {
    return fabs(metric() - other.metric()) < 1e-6; 
}

Circle::Circle(): r_(0) {}

Circle::Circle(double r) {
    if (r < 0) {
        throw "not allowed radius of circle";
    }
    r_ = r;
}

double Circle::metric() const {
    return r_ * r_ * M_PI;
}

double Circle::radius() const {
    return r_;
}

void Circle::print(std::ostream& os) {
    os << "Circle: r=" << r_;
}

void Circle::read(std::istream& is_) {
    is_ >> r_;
}

Ellipse::Ellipse(): a_(0), b_(0) {}

Ellipse::Ellipse(double a, double b) {
    if (a < 0) {
        throw "not allowed a of ellipse";
    }
    if (b < 0) {
        throw "not allowed b of ellipse";
    }
    a_ = a;
    b_ = b;
}

double Ellipse::metric() const {
    return a_ * b_ * M_PI;
}

double Ellipse::isCircle(double eps=1e-6) const {
    return fabs(a_ - b_) < eps;
}

void Ellipse::print(std::ostream& os) {
    os << "Ellipse: a=" << a_ << " b=" << b_;
}

void Ellipse::read(std::istream& is_) {
    is_ >> a_ >> b_;
}

Sector::Sector(): r_(0), theta_(0) {}

Sector::Sector(double r, double theta) {
    if (r < 0) {
        throw "not allowed radius of sector";
    }
    if (theta < 0 || theta > 2 * M_PI) {
        throw "not allowed theta of sector";
    }
    r_ = r;
    theta_ = theta;
}

double Sector::metric() const {
    return r_ * r_ * theta_ / 2;
}

double Sector::isSemicircle(double eps=1e-6) const {
    return fabs(theta_ - M_PI) < eps;
}

void Sector::print(std::ostream& os) {
    os << "Sector: r=" << r_ << " angle=" << theta_;
}

void Sector::read(std::istream& is_) {
    is_ >> r_ >> theta_;
}
