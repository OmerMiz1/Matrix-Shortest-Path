//
// Created by doref on 18/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_POINT_H
#define ALGORITHMICPROGRAMMING2_POINT_H

#include "Cloneable.h"

class Point : Cloneable<Point> {
    int x;
    int y;
public:
    Point(int, int);
    bool operator==(Point* other);
    bool operator<(Point* other);
    int getX();
    int getY();
    Point* clone() const override;
};


#endif //ALGORITHMICPROGRAMMING2_POINT_H
