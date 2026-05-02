#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include<iostream>
#include<fstream>
#include<SFML/Audio.hpp>

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

    sf::Music menuMusic;
    sf::SoundBuffer sandBuffer;
    sf::Sound sandSound;
    sf::Music gameOverMusic;
    sf::SoundBuffer clearbuffer;
    sf::Sound clearSound;
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

    void playSandSound();
    void playGameOverMusic();
    void startMenuMusic();
    void stopAllMusic();
    void playClearSounnd();
};