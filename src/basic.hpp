#pragma once

#include <cmath>
#include <random>

struct Point {
    int x, y;
    Point() : x(0), y(0){};
    Point(int x_, int y_) : x(x_), y(y_) {}
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
