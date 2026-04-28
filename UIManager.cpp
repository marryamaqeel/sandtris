#include "UIManager.hpp"
#include<iostream>

UIManager::UIManager() : currentScore(0),scoreText(font, "", 30)
{
    if (!font.openFromFile("assets/NeonFont.ttf")) {
        std::cerr << "ERROR: Could not load NeonFont.ttf!\n";
    }
    scoreText.setFont(font);
    scoreText.setString("Score: 0");
    scoreText.setFillColor(sf::Color(255,255,255));
    scoreText.setPosition({20.0f,20.0f});
}

void UIManager::addScore(int points)
{
    currentScore += points;
    scoreText.setString("Score: " + std::to_string(currentScore));
}

void UIManager::renderGameplayUI(sf::RenderWindow& window)
{
    sf::RectangleShape bucket;
    bucket.setSize(sf::Vector2f(600.0f, 500.0f)); 
    bucket.setPosition({100.0f, 50.0f});
    bucket.setFillColor(sf::Color::Transparent);
    bucket.setOutlineThickness(2.0f); // <-- FIX: Negative 10!
    bucket.setOutlineColor(sf::Color(100, 50, 200));
    window.draw(bucket);

    // 2. Danger Line
    sf::RectangleShape dangerline;
    dangerline.setSize(sf::Vector2f(600.0f, 2.0f));
    dangerline.setPosition({100.0f, 100.0f});
    dangerline.setFillColor(sf::Color(255, 0, 0, 150));
    window.draw(dangerline);

    // 3. Move the score text UP so it sits neatly above the bucket!
    scoreText.setPosition({100.0f, 10.0f}); 
    window.draw(scoreText);
}


void UIManager::renderMainMenu(sf::RenderWindow& window)
{
    sf::Text text(font,"PRESS ENTER TO PLAY",40);
    // We do NOT need to load the font here, it is already loaded in the constructor!
    text.setFillColor(sf::Color::White);

    // center the text
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({bounds.position.x + (bounds.size.x / 2.f),
                   bounds.position.y + bounds.position.y / 2.f
    });
    text.setPosition(
        {window.getSize().x / 2.f,
        window.getSize().y / 2.f}
    );

    window.draw(text);
}

void UIManager::renderGameOver(sf::RenderWindow& window)
{
    // 1. Game Over Text
    sf::Text overText(font, "GAME OVER", 60);
    overText.setFillColor(sf::Color::Red);
    sf::FloatRect bounds1 = overText.getLocalBounds();
    overText.setOrigin({bounds1.position.x + (bounds1.size.x / 2.0f),
                        bounds1.position.y + (bounds1.size.y / 2.0f)});
    // Place slightly ABOVE the center
    overText.setPosition({window.getSize().x / 2.0f, (window.getSize().y / 2.0f) - 40.0f});

    // 2. Final Score Text
    sf::Text finalScoreText(font, "FINAL SCORE: " + std::to_string(currentScore), 40);
    finalScoreText.setFillColor(sf::Color::White);
    sf::FloatRect bounds2 = finalScoreText.getLocalBounds();
    finalScoreText.setOrigin({bounds2.position.x + (bounds2.size.x / 2.0f),
                              bounds2.position.y + (bounds2.size.y / 2.0f)});
    // Place slightly BELOW the center
    finalScoreText.setPosition({window.getSize().x / 2.0f, (window.getSize().y / 2.0f) + 40.0f});

    // Draw both
    window.draw(overText);
    window.draw(finalScoreText);
}