#include "Game.h"
#include <optional>


Game::Game()
    : window(sf::VideoMode({800, 600}), "Sandtris"),
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
    while (const std::optional event = window.pollEvent())
    {
        // Close window
        if (event->is<sf::Event::Closed>())
            window.close();

        // Keyboard input
        if (const auto* key = event->getIf<sf::Event::KeyPressed>())
        {
            if (key->code == sf::Keyboard::Key::Escape)
                window.close();

            // ENTER → Start / Restart
            if (key->code == sf::Keyboard::Key::Enter)
            {
                if (currentState == GameState::MainMenu)
                    currentState = GameState::Playing;
                else if (currentState == GameState::GameOver)
                    currentState = GameState::MainMenu;
            }

            // P → Pause toggle
            if (key->code == sf::Keyboard::Key::P)
            {
                if (currentState == GameState::Playing)
                    currentState = GameState::Paused;
                else if (currentState == GameState::Paused)
                    currentState = GameState::Playing;
            }
        }

        //Pass input to Tetromino 
        if (currentState == GameState::Playing)
        {
            activeBlock->handleInput(*event);
        }
    }
}

// Update Logic
void Game::update()
{
    if (currentState != GameState::Playing)
        return;

    // Update falling block
    activeBlock->update(playfield);

    // Check if block landed
    if (activeBlock->hasLanded)
    {
        delete activeBlock;
        activeBlock = new Tetromino(4, 0);
    }

    // Sand physics
    playfield->updatePhysics();

    // Line clearing
    int cleared = playfield->clearLines();
    if (cleared > 0)
    {
        ui->addScore(cleared * 100);
    }

    // Game Over condition
    if (playfield->getParticleId(4, 0) != 0)
    {
        currentState = GameState::GameOver;
    }
}

// Rendering
void Game::render()
{
    window.clear();

    if (currentState == GameState::MainMenu)
    {
        // Marryam ka part UI wala
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
        // Optional pause overlay
    }
    else if (currentState == GameState::GameOver)
    {
        playfield->draw(window);
        ui->renderUI(window);
        // Optional game over screen
    }

    window.display();
}