# Tetris
俄罗斯方块小游戏
- 信息
    - 人工智能与计算机学院(系)
    - 班级: 计科2102
    - 学号: 1033210212
    - 姓名: 夏凡                                  
    - 指导老师: 董洪伟
## 控制
A / 方向键左 左
D / 方向键右 右 
W / 方向键上 旋转
S / 方向键下 快速落下

# Code
## main
```C++
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "basic.hpp"
#include "game.hpp"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 900), "Tetris");

    sf::Texture t1, t2, t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/background.png");
    t3.loadFromFile("images/frame.png");
    sf::Sprite background(t2), frame(t3);

    sf::Vector2f scale(2, 2);
    background.setScale(scale);
    frame.setScale(scale);

    int height = 20;
    int width = 10;
    Game::Tetris t(height, width, t1);
    t.setScale(scale);

    int score = 0;

    /*
    string font_path = R"(C:\Windows\Fonts\Microsoft YaHei UI)";
    sf::Font font;
    if (!font.loadFromFile(font_path)) {
        // error...
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Hello");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.move(416, 0);
    */

    int dx = 0;
    bool rotate = false;
    sf::Clock clock;
    float timer = 0, delay = 0.3;
    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
            if (e.type == sf::Event::KeyPressed) {
                switch (e.key.code) {
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                    rotate = true;
                    break;
                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                    dx = -1;
                    break;
                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                    dx = 1;
                    break;
                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                    delay = 0;
                    break;
                case sf::Keyboard::Q:
                    window.close();
                    break;
                default:
                    break;
                }
            }
        }

        ///////Move//////
        t.move_x(dx);
        dx = 0;
        if (rotate) {
            t.rotate();
            rotate = false;
        }
        if (timer > delay) {
            t.move_y();
            timer = 0;
        }
        delay = 0.3;
        score += t.check_lines();

        /////////draw//////////
        window.clear(sf::Color::White);
        window.draw(background);
        window.draw(t);
        window.draw(frame);
        // window.draw(text);

        window.display();
    }

    return 0;
}

```
## basic
```C++
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
    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(engine);
}
```
## game
```C++
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

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

class Tetris : public sf::Drawable, public sf::Transformable {
private:
    struct Tetromino {
        std::vector<Point> pos;
        int shape;
        int colour;
        Tetromino() : pos(4), shape(0), colour(0) {}
        void rand() {
            shape = rand_num(0, Shape::max - 1);
            colour = rand_num(0, Colour::max - 1);
            for (int i = 0; i < 4; i++) {
                pos[i] = Shape::get(shape, i);
            }
        }
    };

    int height, width;
    std::vector<std::vector<int>> matrix;

    Tetromino now, backup;
    sf::Texture Tetromino_t;
    sf::Vector2f factors;

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

    void init_Tetromino() {
        now.rand();
        backup = now;
    }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        sf::Sprite s(Tetromino_t);
        s.setScale(factors);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (matrix[i][j] == -1) {
                    continue;
                }
                s.setTextureRect(sf::IntRect(matrix[i][j] * 18, 0, 18, 18));
                s.setPosition(j * 18 * factors.x, i * 18 * factors.y);
                s.move(28 * factors.x, 31 * factors.y);  // offset
                target.draw(s, states);
            }
        }

        for (int i = 0; i < 4; i++) {
            s.setTextureRect(sf::IntRect(now.colour * 18, 0, 18, 18));
            s.setPosition(now.pos[i].x * 18 * factors.x, now.pos[i].y * 18 * factors.y);
            s.move(28 * factors.x, 31 * factors.y);  // offset
            target.draw(s, states);
        }
    }

public:
    Tetris(int _height, int _width, sf::Texture _Tetromino_t)
        : height(_height),
          width(_width),
          matrix(_height, std::vector<int>(_width, -1)),
          Tetromino_t(_Tetromino_t) {
        init_Tetromino();
    }

    void resize(int _height, int _width) {
        height = _height;
        width = _width;
        matrix.resize(_height, std::vector<int>(_width, -1));
        init_Tetromino();
    }

    void move_x(int dx) {
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

    void move_y() {
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
            init_Tetromino();
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

    int check_lines() {
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

    void setScale(const sf::Vector2f &_factors) {
        factors = _factors;
    }
};

}  // namespace Game

```

## run
- xmake
- ./init.ps1
- xmake run