#pragma once

#include <cmath>
#include <random>

struct Point {
    int x;
    int y;
    Point() : x(0), y(0){};
    Point(int _x, int _y) : x(_x), y(_y) {}
};

int rand_num(int min, int max) {
    std::random_device seed;
    std::ranlux48 engine(seed());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(engine);
}
