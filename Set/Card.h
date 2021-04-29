#pragma once

#include <string>

class Card {
private:
    unsigned int number;
    unsigned int shape;
    unsigned int shading;
    unsigned int color;

public:
    Card(unsigned int number, unsigned int shape, unsigned int shading, unsigned int color) noexcept;
    Card() = delete;
    ~Card() = default;

    unsigned int getNumber() const;
    unsigned int getShape() const;
    unsigned int getShading() const;
    unsigned int getColor() const;
    std::string toString();
};