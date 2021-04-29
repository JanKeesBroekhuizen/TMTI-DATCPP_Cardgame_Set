#include <sstream>
#include "Card.h"

Card::Card(unsigned int number, unsigned int shape, unsigned int shading, unsigned int color) noexcept
    : number(number), shape(shape), shading(shading), color(color) {
}

unsigned int Card::getNumber()  const {
    return number;
}

unsigned int Card::getShape()  const {
    return shape;
}

unsigned int Card::getShading()  const {
    return shading;
}

unsigned int Card::getColor()  const {
    return color;
}

std::string Card::toString() {
    std::stringstream os;
    os << "Number: " << number << " Shape: " << shape << " Shading: " << shading << " Color: " << color << std::endl;
    return os.str();
}