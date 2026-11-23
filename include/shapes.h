#pragma once

#include <ostream>
#include <istream>
#include <cmath>

class Shape2D {
public:
    virtual double metric() const;
    virtual void print(std::ostream&);
    virtual void read(std::istream&);
    friend std::ostream& operator<<(std::ostream&, Shape2D);
    friend std::istream& operator>>(std::istream&, Shape2D);
    operator double() const;
    bool operator==(const Shape2D&);
};

class Circle: Shape2D {
    double r_{};
public:
    Circle();
    Circle(double r);
    double metric() const override;
    void print(std::ostream&) override;
    void read(std::istream&) override;
    double radius() const;
};

class Ellipse: Shape2D {
    double a_{}, b_{};
public:
    Ellipse();
    Ellipse(double a, double b);
    double metric() const override;
    void print(std::ostream&) override;
    void read(std::istream&) override;
    double isCircle(double) const;
};

class Sector: Shape2D {
    double r_{}, theta_{};
public:
    Sector();
    Sector(double r, double theta);
    double metric() const override;
    void print(std::ostream&) override;
    void read(std::istream&) override;
    double isSemicircle(double) const;
};