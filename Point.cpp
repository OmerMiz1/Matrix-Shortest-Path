//
// Created by doref on 18/01/2020.
//

#include <math.h>

#include "Point.h"

Point::Point(int xVal, int yVal): x(xVal), y(yVal) {}

Point::Point(Point const &other) : x(other.x), y(other.y) {}

/**
 * Checks equality between this point and another one
 * @param other the other point we want to check
 * @return true - if the points are equal, false - otherwise
 */
bool Point::operator==(const Point &other) const{
    return (this->x == other.x) && (this->y == other.y);
}

/**
 * Returns the x value of the point
 * @return the x value of the point
 */
int Point::getX() const{
    return this->x;
}

/**
 * Returns the y value of the point
 * @return the y value of the point
 */
int Point::getY() const{
    return this->y;
}

/**
 * Returns the distance between this point and an other point
 * @param other the other point
 * @return the distance between the points
 */
double Point::distance(Point *other) const {
    double subX = this->x - other->x;
    double subY = this->y - other->y;
    double subXPowerTwo = subX * subX;
    double subYPowerTwo = subY * subY;
    return (sqrt(subXPowerTwo+subYPowerTwo));
}

/**
 * Overridden in order to create comparator at State<T>
 * @param other
 * @return
 */
bool Point::operator<(const Point &other) const{
    /*TODO: Make sure its !(this==other) and that auto correct didnt change it*/
    return !(*this == other);
}

Point* Point::clone() const {
    return new Point(*this);
}

string Point::str() const {
    /*TODO possible issues with parallel server?*/
    return "(" + to_string(x) + "," + to_string(y) + ")";
}



