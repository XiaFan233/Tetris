#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "basic.hpp"
#include "game.hpp"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");
    window.setSize(sf::Vector2u(640, 960));

    const string tilesPath      = R"(.\assets\tiles.png)";
    const string backgroundPath = R"(.\assets\background.png)";
    const string framePath      = R"(.\assets\frame.png)";
    const string fontPath       = R"(.\assets\cambria.ttc)";

    sf::Texture tilesTexture, backgroundTexture, frameTexture;
    if (!tilesTexture.loadFromFile(tilesPath)) {
        cerr << "[error] tilesTexture.loadFromFile fail!\n";
    }
    if (!backgroundTexture.loadFromFile(backgroundPath)) {
        cerr << "[error] backgroundTexture.loadFromFile fail!\n";
    }
    if (!frameTexture.loadFromFile(framePath)) {
        cerr << "[error] frameTexture.loadFromFile fail!\n";
    }
    sf::Font font;
    if (!font.loadFromFile(fontPath)) {
        cerr << "[error] font.loadFromFile fail!\n";
    }

    sf::Text titleText("Tetris", font, 24);
    titleText.setFillColor(sf::Color::Black);
    titleText.setStyle(sf::Text::Bold | sf::Text::Italic);
    titleText.move(250, 10);

    sf::Text scoreText("Score:", font, 24);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setStyle(sf::Text::Bold);
    scoreText.move(250, 200);

    string scoreStr = "0";
    sf::Text score(scoreStr, font, 24);
    score.setFillColor(sf::Color::Red);
    score.setStyle(sf::Text::Bold);
    score.move(250, 250);

    const int height = 20;
    const int width = 10;
    Game::Tetris tetris(height, width, tilesTexture);
    sf::Sprite background(backgroundTexture), frame(frameTexture);

    sf::Clock clock;
    float timer = 0, delay = 0.3;
    int scoreNum = 0;
    int dx = 0;
    bool rotate = false;
    while (window.isOpen()) {
        // Time
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        // Key
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
                }
            }
        }

        // Move
        tetris.moveX(dx);
        dx = 0;
        if (rotate) {
            tetris.rotate();
            rotate = false;
        }
        if (timer > delay) {
            tetris.moveY();
            timer = 0;
        }
        delay = 0.3;
        int add = tetris.checkLines();
        if(add > 0) {
            scoreNum += add;
            scoreStr = to_string(scoreNum);
            cerr << "[score] " << scoreNum << "\n";
        }

        // Draw
        window.clear(sf::Color::White);
        window.draw(background);
        window.draw(tetris);
        window.draw(frame);
        window.draw(titleText);
        window.draw(scoreText);

        // Draw Score
        score.setString(scoreStr);
        window.draw(score);

        window.display();
    }
    cerr << "[Game End]\n";

    return 0;
}
