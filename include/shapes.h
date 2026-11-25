#pragma once

#include <ostream>
#include <istream>
#include <cmath>

class Shape2D {
public:
    virtual double metric() const = 0;
    virtual void print(std::ostream&) = 0;
    virtual void read(std::istream&) = 0;
    virtual Shape2D* copy() = 0;
    friend std::ostream& operator<<(std::ostream&, Shape2D&);
    friend std::istream& operator>>(std::istream&, Shape2D&);
    operator double() const;
    bool operator==(const Shape2D&);
    virtual ~Shape2D() = default;
};

class Circle: public Shape2D {
    double r_{};
public:
    Circle();
    Circle(double r);
    double metric() const override;
    void print(std::ostream&) override;
    void read(std::istream&) override;
    Shape2D* copy() override;
    double radius() const;
};

class Ellipse: public Shape2D {
    double a_{}, b_{};
public:
    Ellipse();
    Ellipse(double a, double b);
    double metric() const override;
    void print(std::ostream&) override;
    void read(std::istream&) override;
    Shape2D* copy() override;
    double isCircle(double) const;
};

class Sector: public Shape2D {
    double r_{}, theta_{};
public:
    Sector();
    Sector(double r, double theta);
    double metric() const override;
    void print(std::ostream&) override;
    void read(std::istream&) override;
    Shape2D* copy() override;
    double isSemicircle(double) const;
};