#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class UIManager {
private:
    sf::Font font;
    sf::Text scoreText;
    int currentScore;

public:
    UIManager();
    void addScore(int points);
    void renderUI(sf::RenderWindow& window);
};