//
// Created by Dor Refaeli on 18/01/2020.
//

#ifndef ALGORITHMICPROGRAMMING2_POINT_H
#define ALGORITHMICPROGRAMMING2_POINT_H

#include <sstream>
#include <iomanip>
#include "Cloneable.h"
#include "Stringable.h"

class Point : Cloneable<Point>, Stringable<Point> {
    int x;
    int y;
public:
    Point()=default;
    Point(int, int);
    Point(const Point &other);
    enum Direction {Up, Down, Left, Right, Same};
    Direction getDirectionTo(const Point &other) const;
    string getDirectionToStr(const Point &other) const;
    int getX() const;
    int getY() const;
    int manhattanHeuristicDistance(Point *other) const;
    bool operator==(const Point &other) const;
    bool operator<(const Point &other) const;

    int uniq() {
        stringstream strXTemp;
        strXTemp << setw(10) << setfill('0') << x;
        string strX = strXTemp.str();
        stringstream strYTemp;
        strYTemp << setw(10) << setfill('0') << y;
        string strY = strYTemp.str();
        ::hash<int> hasher;
        size_t h1 = std::hash<std::string>{}(strX);
        size_t h2 = std::hash<std::string>{}(strY);
        return h1 ^ (h2 << 1);
    }

    string str() const override;
    Point* clone() const override;
};

#endif //ALGORITHMICPROGRAMMING2_POINT_H
