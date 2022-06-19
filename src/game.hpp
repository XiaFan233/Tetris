#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <numbers>

constexpr double Pi = std::numbers::pi;

#include "basic.hpp"

namespace Game {
namespace Shape {
/**
 * @brief hahahaha
 * 0 1
 * 2 3
 * 4 5
 * 6 7
 */
constexpr int pos[7][4] = {
    1, 3, 5, 7,  // I
    2, 4, 5, 7,  // Z
    3, 5, 4, 6,  // S
    3, 5, 4, 7,  // T
    2, 3, 5, 7,  // L
    3, 5, 7, 6,  // J
    2, 3, 4, 5,  // O
};

constexpr int max = 7;

Point get(int shape, int i) {
    int num = pos[shape][i];
    return Point(num % 2, num / 2);
}
}  // namespace Shape

namespace Colour {
constexpr int max = 7;
}

struct Tetromino {
    std::vector<Point> pos;
    int shape;
    int colour;
    Tetromino() : pos(4), shape(0), colour(0) {}
};

class Tetris : public sf::Drawable, public sf::Transformable {
private:
    int height, width;
    std::vector<std::vector<int>> matrix;

    Tetromino next, now, backup;
    int nextShape, nextColour;
    sf::Texture TetrominoTexture;
    Randomer<int> RShape, RColour;

    bool check(Tetromino &t) {
        for (int i = 0; i < 4; i++) {
            int x = t.pos[i].x;
            int y = t.pos[i].y;
            // std::cerr << x << " " << y << "\n";
            if (x < 0 || x >= width || y >= height) {
                return false;
            } else if (matrix[y][x] != -1) {
                return false;
            }
        }
        return true;
    }

    void initTetromino(Tetromino &tetromino) {
        tetromino.shape = RShape();
        tetromino.colour = RColour();
        for (int i = 0; i < 4; i++) {
            tetromino.pos[i] = Shape::get(tetromino.shape, i);
        }
    }

    void nextTetromino() {
        now = next;
        backup = now;
        initTetromino(next);
    }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        sf::Sprite TetrominoSprite(TetrominoTexture);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (matrix[i][j] == -1) {
                    continue;
                }
                TetrominoSprite.setTextureRect(sf::IntRect(matrix[i][j] * 18, 0, 18, 18));
                TetrominoSprite.setPosition(j * 18, i * 18);
                TetrominoSprite.move(28, 31);
                target.draw(TetrominoSprite, states);
            }
        }

        for (int i = 0; i < 4; i++) {
            TetrominoSprite.setTextureRect(sf::IntRect(now.colour * 18, 0, 18, 18));
            TetrominoSprite.setPosition(now.pos[i].x * 18, now.pos[i].y * 18);
            TetrominoSprite.move(28, 31);
            target.draw(TetrominoSprite, states);
        }

        for (int i = 0; i < 4; i++) {
            TetrominoSprite.setTextureRect(sf::IntRect(next.colour * 18, 0, 18, 18));
            TetrominoSprite.setPosition(next.pos[i].x * 18, next.pos[i].y * 18);
            TetrominoSprite.move(250, 80);
            target.draw(TetrominoSprite, states);
        }
    }

public:
    Tetris(int height_, int width_, sf::Texture _TetrominoTexture) : 
      height(height_),
      width(width_),
      matrix(height_, std::vector<int>(width_, -1)),
      TetrominoTexture(_TetrominoTexture),
      RShape(0, Shape::max - 1),
      RColour(0, Colour::max - 1)
    {
        initTetromino(next);
        nextTetromino();
    }

    void resize(int height_, int width_) {
        height = height_;
        width = width_;
        matrix.resize(height_, std::vector<int>(width_, -1));
        nextTetromino();
    }

    void moveX(int dx) {
        for (int i = 0; i < 4; i++) {
            now.pos[i].x += dx;
        }
        if (check(now)) {
            for (int i = 0; i < 4; i++) {
                backup.pos[i].x = now.pos[i].x;
            }
        } else {
            for (int i = 0; i < 4; i++) {
                now.pos[i].x = backup.pos[i].x;
            }
        }
    }

    void moveY() {
        // std::cerr << now.shape << "\n";
        for (int i = 0; i < 4; i++) {
            now.pos[i].y++;
        }
        if (check(now)) {
            for (int i = 0; i < 4; i++) {
                backup.pos[i].y = now.pos[i].y;
            }
        } else {
            for (int i = 0; i < 4; i++) {
                int x = backup.pos[i].x;
                int y = backup.pos[i].y;
                matrix[y][x] = backup.colour;
            }
            nextTetromino();
        }
    }

    void rotate() {
        Point p = now.pos[1];  // center of rotation
        for (int i = 0; i < 4; i++) {
            int x = now.pos[i].y - p.y;
            int y = now.pos[i].x - p.x;
            now.pos[i].x = p.x - x;
            now.pos[i].y = p.y + y;
        }
        if (check(now)) {
            for (int i = 0; i < 4; i++) {
                backup.pos[i] = now.pos[i];
            }
        } else {
            for (int i = 0; i < 4; i++) {
                now.pos[i] = backup.pos[i];
            }
        }
    }

    int checkLines() {
        int res = 0;
        for (int i = height - 1, k = height - 1; i >= 0; i--) {
            int count = 0;
            for (int j = 0; j < width; j++) {
                if (matrix[i][j] != -1) {
                    count++;
                }
                matrix[k][j] = matrix[i][j];
            }
            if (count < width) {
                k--;
            } else {
                res++;
            }
        }
        return res;
    }
};
}  // namespace Game
