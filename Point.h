//
// Created by Dor Refaeli on 18/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_POINT_H
#define ALGORITHMICPROGRAMMING2_POINT_H

#include "Cloneable.h"
#include "Stringable.h"

class Point : Cloneable<Point>, Stringable<Point> {
    int x;
    int y;
public:
    Point()=default;
    Point(int, int);
    explicit Point(const Point &other);
    enum Direction {Up, Down, Left, Right, Same};
    Direction getDirectionTo(const Point &other) const;
    string getDirectionToStr(Direction direction) const;
    int getX() const;
    int getY() const;
    double distance(Point *other) const;
    bool operator==(const Point &other) const;
    bool operator<(const Point &other) const;

    string str() const override;
    Point* clone() const override;
};

#endif //ALGORITHMICPROGRAMMING2_POINT_H
