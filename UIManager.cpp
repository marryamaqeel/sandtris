#include "UIManager.hpp"
#include <iostream>

UIManager::UIManager() : currentScore(0), scoreText(font, "", 30), highScoreText(font, "", 30) ,easyText(font, "", 30) , medText(font, "", 30) , HardText(font, "", 30) ,titleText(font, "", 30)
{
    if (!font.openFromFile("assets/NeonFont.ttf"))
    {
        std::cerr << "ERROR: Could not load NeonFont.ttf!\n";
    }
    scoreText.setFont(font);
    scoreText.setString("Score: 0");
    scoreText.setFillColor(sf::Color(255, 255, 255));
    scoreText.setPosition({20.0f, 20.0f});

    std::ifstream loadfile("highscore.txt");
    if (loadfile.is_open())
    {
        loadfile >> highScore[0] >> highScore[1] >> highScore[2];
        loadfile.close();
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            highScore[i] = 0;
        }
        
    }

    highScoreText.setFont(font);
    highScoreText.setString("High Score: " + std::to_string(highScore[0]));
    highScoreText.setFillColor(sf::Color(255, 215, 0));
    highScoreText.setPosition({450.0f, 10.0f});

    // title title text

    titleText.setFont(font);
    titleText.setString("SANDTRIS");
    titleText.setCharacterSize(80);
    titleText.setFillColor(sf::Color::White);
    titleText.setOutlineThickness(5.0f);
    titleText.setOutlineColor(sf::Color(138, 0, 196));
    titleText.setStyle(sf::Text::Bold);

    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin({titleBounds.position.x + titleBounds.size.x / 2.0f, 
                         titleBounds.position.y + titleBounds.size.y / 2.0f});
    titleText.setPosition({400.0f, 120.0f});


    // easy medium hard buttons
    sf::Vector2f buttonSize({250.0f,60.0f});

    easyButton.setSize(buttonSize);
    easyButton.setFillColor(sf::Color::Transparent);
    easyButton.setOutlineThickness(3.0f);
    easyButton.setOutlineColor(sf::Color(57,255,20));
    easyButton.setOrigin({buttonSize.x/2.0f,buttonSize.y/2.0f});
    easyButton.setPosition({400.0f,280.0f});

    medButton.setSize(buttonSize);
    medButton.setFillColor(sf::Color::Transparent);
    medButton.setOutlineThickness(3.0f);
    medButton.setOutlineColor(sf::Color(255,255,0));
    medButton.setOrigin({buttonSize.x/2.0f,buttonSize.y/2.0f});
    medButton.setPosition({400.0f,380.0f});

    hardButton.setSize(buttonSize);
    hardButton.setFillColor(sf::Color::Transparent);
    hardButton.setOutlineThickness(3.0f);
    hardButton.setOutlineColor(sf::Color(255,20,20));
    hardButton.setOrigin({buttonSize.x/2.0f,buttonSize.y/2.0f});
    hardButton.setPosition({400.0f,480.0f});

    easyText.setFont(font);
    easyText.setString("EASY");
    easyText.setCharacterSize(30);
    easyText.setFillColor(sf::Color(57,255,20));
    easyText.setStyle(sf::Text::Bold);
    sf::FloatRect b1 = easyText.getLocalBounds();
    easyText.setOrigin({b1.position.x + b1.size.x / 2.0f, b1.position.y + b1.size.y / 2.0f});
    easyText.setPosition(easyButton.getPosition());

    medText.setFont(font); 
    medText.setString("MEDIUM"); 
    medText.setCharacterSize(30);
    medText.setFillColor(sf::Color(255,255,0));
    medText.setStyle(sf::Text::Bold);
    sf::FloatRect b2 = medText.getLocalBounds();
    medText.setOrigin({b2.position.x + b2.size.x / 2.0f, b2.position.y + b2.size.y / 2.0f});
    medText.setPosition(medButton.getPosition());

    HardText.setFont(font); 
    HardText.setString("HARD"); 
    HardText.setCharacterSize(30);
    HardText.setFillColor(sf::Color(255,20,20));
    HardText.setStyle(sf::Text::Bold);
    sf::FloatRect b3 = HardText.getLocalBounds();
    HardText.setOrigin({b3.position.x + b3.size.x / 2.0f, b3.position.y + b3.size.y / 2.0f});
    HardText.setPosition(hardButton.getPosition());
}

void UIManager::saveHighScore(int difficulty)
{
    std::ofstream savefile("highscore.txt");
    if (savefile.is_open())
    {
        savefile << highScore[0] << " "<< highScore[1] <<" "<< highScore[2];
        savefile.close();
    }
}
void UIManager::addScore(int points,int difficulty)
{
    currentScore += points;
    scoreText.setString("Score: " + std::to_string(currentScore));

    int index = difficulty - 2;
    if (currentScore > highScore[index])
    {
        highScore[index] = currentScore;
        highScoreText.setString("High Score: " + std::to_string(highScore[index]));
    }
}

void UIManager::renderGameplayUI(sf::RenderWindow &window)
{

    window.draw(highScoreText);
    sf::RectangleShape bucket;
    bucket.setSize(sf::Vector2f(600.0f, 500.0f));
    bucket.setPosition({100.0f, 50.0f});
    bucket.setFillColor(sf::Color::Transparent);
    bucket.setOutlineThickness(10.0f);

    bucket.setOutlineColor(sf::Color(100, 50, 200));
    window.draw(bucket);
    // 2. Danger Line
    sf::RectangleShape dangerline;
    dangerline.setSize(sf::Vector2f(600.0f, 2.0f));
    dangerline.setPosition({100.0f, 100.0f});
    dangerline.setFillColor(sf::Color(255, 0, 0, 150));
    window.draw(dangerline);

    scoreText.setPosition({100.0f, 10.0f});
    window.draw(scoreText);
}

void UIManager::renderMainMenu(sf::RenderWindow &window)
{
    
    window.draw(titleText);
    window.draw(easyButton);
    window.draw(medButton);
    window.draw(hardButton);
    window.draw(HardText);
    window.draw(easyText);
    window.draw(medText);
}

void UIManager::renderGameOver(sf::RenderWindow &window , int difficulty)
{

    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(overlay);

    // 1. Game Over Text
    sf::Text overText(font, "GAME OVER", 60);
    overText.setFillColor(sf::Color::Red);
    sf::FloatRect bounds1 = overText.getLocalBounds();
    overText.setOrigin({bounds1.position.x + (bounds1.size.x / 2.0f),
                        bounds1.position.y + (bounds1.size.y / 2.0f)});
    // Place slightly ABOVE the center
    overText.setPosition({window.getSize().x / 2.0f, (window.getSize().y / 2.0f) - 100.0f});

    // restart text
    sf::Text restartText(font, "Press ENTER to Restart\nPress ESC for Main Menu", 30);
    restartText.setFillColor(sf::Color::White);
    sf::FloatRect b = restartText.getGlobalBounds();
    restartText.setOrigin({b.position.x + (b.size.x / 2.0f), b.position.y + (b.size.y / 2.0f)});
    restartText.setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f - 30.0f});

    // 2. Final Score Text
    sf::Text finalScoreText(font, "FINAL SCORE: " + std::to_string(currentScore), 40);
    finalScoreText.setFillColor(sf::Color::White);
    sf::FloatRect bounds2 = finalScoreText.getLocalBounds();
    finalScoreText.setOrigin({bounds2.position.x + (bounds2.size.x / 2.0f),
                              bounds2.position.y + (bounds2.size.y / 2.0f)});
    // Place slightly BELOW the center
    finalScoreText.setPosition({window.getSize().x / 2.0f, (window.getSize().y / 2.0f) + 40.0f});

    sf::Text highText(font, "HIGH SCORE: " + std::to_string(highScore[difficulty - 2]), 40);
    highText.setFillColor(sf::Color::Cyan);
    sf::FloatRect bounds3 = highText.getLocalBounds();
    highText.setOrigin({bounds3.position.x + (bounds3.size.x / 2.0f),
                        bounds3.position.y + (bounds3.size.y / 2.0f)});
    highText.setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f + 80.0f});

    window.draw(overText);
    window.draw(finalScoreText);
    window.draw(restartText);
    window.draw(highText);
}

void UIManager::resetScore()
{
    currentScore = 0;
    scoreText.setString("Score: 0");
}

void UIManager::renderPause(sf::RenderWindow &window)
{
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f({window.getSize().x, window.getSize().y}));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(overlay);

    sf::Text pauseText(font, "Paused", 60);
    pauseText.setFillColor(sf::Color::White);
    sf::FloatRect bounds = pauseText.getLocalBounds();
    pauseText.setOrigin({bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f});

    pauseText.setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f});

    window.draw(pauseText);
}

int UIManager::handleMenuClick(sf::Vector2i mousepos)
{
    sf::Vector2f pos(static_cast<float>(mousepos.x), 
    static_cast<float>(mousepos.y));

    if (easyButton.getGlobalBounds().contains(pos)) return 2; // 2 Colors
    if (medButton.getGlobalBounds().contains(pos)) return 3;  // 3 Colors
    if (hardButton.getGlobalBounds().contains(pos)) return 4; // 4 Colors
    
    return 0;
}

void UIManager::updateHighScoreDisplay(int difficulty) 
{
    int index = difficulty - 2;
    highScoreText.setString("High Score: " + std::to_string(highScore[index]));
}