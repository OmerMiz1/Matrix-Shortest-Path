//
// Created by doref on 18/01/2020.
//

#include <math.h>

#include "Point.h"

Point::Point(int xVal, int yVal): x(xVal), y(yVal) {}

/**
 * Checks equality between this point and another one
 * @param other the other point we want to check
 * @return true - if the points are equal, false - otherwise
 */
bool Point::operator==(Point *other) {
    return (this->x == other->x) && (this->y == other->y);
}

/**
 * Returns the x value of the point
 * @return the x value of the point
 */
int Point::getX() {
    return this->x;
}

/**
 * Returns the y value of the point
 * @return the y value of the point
 */
int Point::getY() {
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
bool Point::operator<(Point *other) {
    /*TODO: Make sure its !(this==other) and that auto correct didnt change it*/
    return !(this == other);
}

Point* Point::clone() const {
    return new Point(*this);
}

