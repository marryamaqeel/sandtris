#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include<iostream>
#include<fstream>

class UIManager {
private:
    sf::Font font;
    sf::Text scoreText;
    sf::Text highScoreText;
    sf::RectangleShape easyButton;
    sf::RectangleShape medButton;
    sf::RectangleShape hardButton;
    sf::Text easyText;
    sf::Text medText;
    sf::Text HardText;
    sf::Text titleText;
    int currentScore;
    int highScore[3];

public:
    UIManager();
    void addScore(int points,int difficulty);
    void renderGameplayUI(sf::RenderWindow& window);
    void renderMainMenu(sf::RenderWindow& window);
    void renderGameOver(sf::RenderWindow& window , int difficulty);
    void saveHighScore(int difficulty);
    void resetScore();
    void renderPause(sf::RenderWindow& window);
    int handleMenuClick(sf::Vector2i mousePos);
    void updateHighScoreDisplay(int difficulty);
};