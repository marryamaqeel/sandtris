#include "Game.h"

Game::Game()
    : window(sf::VideoMode(800, 600), "Sandtris"),
      isRunning(true),
      currentState(GameState::MainMenu),
      currentDifficulty(1)
{
    window.setFramerateLimit(60);

    playfield = new Grid(10, 20);
    activeBlock = new Tetromino(4, 0);
    ui = new UIManager();
}

Game::~Game()
{
    delete playfield;
    delete activeBlock;
    delete ui;
}

void Game::run()
{
    while (window.isOpen() && isRunning)
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();

            // State control
            if (event.key.code == sf::Keyboard::Enter)
            {
                if (currentState == GameState::MainMenu)
                    currentState = GameState::Playing;
                else if (currentState == GameState::GameOver)
                    currentState = GameState::MainMenu;
            }

            if (event.key.code == sf::Keyboard::P)
            {
                if (currentState == GameState::Playing)
                    currentState = GameState::Paused;
                else if (currentState == GameState::Paused)
                    currentState = GameState::Playing;
            }
        }

        // Only pass input when playing
        if (currentState == GameState::Playing)
        {
            activeBlock->handleInput(event);
        }
    }
}

void Game::update()
{
    if (currentState != GameState::Playing)
        return;

    // Update tetromino
    activeBlock->update(playfield);

    // Clear lines and update score
    int cleared = playfield->clearLines();
    if (cleared > 0)
    {
        ui->addScore(cleared * 100);
    }

    if (playfield->getParticleId(4, 0) != 0)
    {
        currentState = GameState::GameOver;
    }
}

void Game::render()
{
    window.clear();

    if (currentState == GameState::MainMenu)
    {
         ui->renderMenu(window);
    }
    else if (currentState == GameState::Playing)
    {
        playfield->draw(window);
        activeBlock->draw(window);
        ui->renderUI(window);
    }
    else if (currentState == GameState::Paused)
    {
        playfield->draw(window);
        activeBlock->draw(window);
        ui->renderUI(window);
    }
    else if (currentState == GameState::GameOver)
    {
        playfield->draw(window);
        ui->renderUI(window);
    }

    window.display();
}