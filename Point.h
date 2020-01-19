//
// Created by doref on 18/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_POINT_H
#define ALGORITHMICPROGRAMMING2_POINT_H


class Point {
    int x;
    int y;
public:
    Point(int, int);
    bool operator==(Point* other);
    int getX();
    int getY();
};


#endif //ALGORITHMICPROGRAMMING2_POINT_H
