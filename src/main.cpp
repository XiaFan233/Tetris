#include <SFML/Graphics.hpp>

#include "basic.hpp"
#include "game.hpp"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 960), "The Game!");

    sf::Texture t1, t2, t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/background.png");
    t3.loadFromFile("images/frame.png");
    sf::Sprite background(t2), frame(t3);
    background.setScale(sf::Vector2f(2, 2));
    frame.setScale(sf::Vector2f(2, 2));

    int height = 20;
    int width = 10;
    Game::Tetris t(height, width, t1);
    t.setScale(sf::Vector2f(2, 2));

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
        t.check_lines();

        /////////draw//////////
        window.clear(sf::Color::White);
        window.draw(background);
        window.draw(t);
        window.draw(frame);

        window.display();
    }

    return 0;
}
