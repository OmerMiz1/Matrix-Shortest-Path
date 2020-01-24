//
// Created by Dor Refaeli on 18/01/2020.
//

#include <math.h>

#include "Point.h"

Point::Point(int xVal, int yVal): x(xVal), y(yVal) {}

Point::Point(const Point &other) : x(other.x), y(other.y) {}

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
int Point::manhattanHeuristicDistance(Point *other) const {
    int subX = abs(this->x - other->x);
    int subY = abs(this->y - other->y);
    return (subX + subY);
}

/**
 * Overridden in order to create comparator at State<T>
 * @param other
 * @return
 */
bool Point::operator<(const Point &other) const{
    return !(*this == other);
}

Point* Point::clone() const {
    return new Point(*this);
}

string Point::str() const {
    return "(" + to_string(x) + "," + to_string(y) + ")";
}

Point::Direction Point::getDirectionTo(const Point &other) const {
    if (this->x < other.x) {
        return Down;
    } else if (this->x > other.x) {
        return Up;
    } else if (this->y < other.y) {
        return Right;
    } else if (this->y > other.y) {
        return Left;
    } else {
        return Same;
    }
}

string Point::getDirectionToStr(const Point &other) const {
    auto direction = this->getDirectionTo(other);
    switch(direction) {
        case Up: {
            return "Up";
        }
        case Down: {
            return "Down";
        }
        case Left: {
            return "Left";
        }
        case Right: {
            return "Right";
        }
        case Same: {
            return "Same";
        }
        default: {
            return "ERROR";
        }
    }
}




