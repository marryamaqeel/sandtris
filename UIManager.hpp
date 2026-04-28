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
    void renderGameplayUI(sf::RenderWindow& window);
    void renderMainMenu(sf::RenderWindow& window);
    void renderGameOver(sf::RenderWindow& window);
};