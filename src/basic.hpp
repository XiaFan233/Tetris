#pragma once

#include <cmath>
#include <random>

struct Point {
    int x;
    int y;
    Point() : x(0), y(0){};
    Point(int _x, int _y) : x(_x), y(_y) {}
};

template <typename T> class Randomer {
private:
    unsigned int seed;
    std::mt19937 engine;
    std::uniform_int_distribution<T> distribution;

public:
    Randomer(T min, T max) : 
      seed(std::random_device()()),
      engine(seed), 
      distribution(min, max) {}

    T operator()() {
        std::cerr << "[Randomer] " << seed << "\n";
        return distribution(engine);
    }
};
