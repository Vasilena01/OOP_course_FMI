#include "Point.h"

int16_t Point::getX() const
{
    return x;
}

int16_t Point::getY() const
{
    return y;
}

bool Point::getIsDisabled() const
{
    return isDisabled;
}

void Point::setX(int16_t x)
{
    this->x = x;
}

void Point::setY(int16_t y)
{
    this->y = y;
}

void Point::setIsDisabled(bool flag)
{
    isDisabled = flag;
}
