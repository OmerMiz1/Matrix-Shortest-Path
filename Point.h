//
// Created by Dor Refaeli on 18/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_POINT_H
#define ALGORITHMICPROGRAMMING2_POINT_H

#include "Cloneable.h"

class Point : Cloneable<Point> {
    int x;
    int y;
public:
    Point()=default;
    Point(int, int);
    explicit Point(Point const &other);
    bool operator==(const Point &other) const;
    bool operator<(const Point &other) const;
    int getX() const;
    int getY() const;
    double distance(Point *other) const;
    Point* clone() const override;
};


#endif //ALGORITHMICPROGRAMMING2_POINT_H
