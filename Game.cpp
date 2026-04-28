#include "Game.hpp"
#include<SFML/Graphics.hpp>

sf::Clock deltaClock;


Game::Game() : window(sf::VideoMode({800,600}), "SandTris")
{
    window.setFramerateLimit(60); 
    playfield = new grid(150,125);
    activeBlock = new Tetromino();
    ui = new UIManager();
    currentState = GameState::MainMenu;
}

Game::~Game()
{
    delete playfield;
    delete activeBlock;
    delete ui;
}

void Game::run()
{
    while (window.isOpen())
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
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        if (event->is<sf::Event::KeyPressed>())
        {
            const auto* key = event->getIf<sf::Event::KeyPressed>();
        }
        if (currentState == GameState::MainMenu)
        {
            if (event->is<sf::Event::KeyPressed>())
            {
                const auto& keyEvent = event->getIf<sf::Event::KeyPressed>();

                if (keyEvent && keyEvent->code == sf::Keyboard::Key::Enter)
                {
                    currentState = GameState::Playing;
                }
            }
        }

        if (currentState == GameState::Playing)
        {
            activeBlock->handleInput(event.value(),playfield);
        }

    }
    
}

void Game::update()
{
    if(currentState == GameState::Playing)
    {
        float dt = deltaClock.restart().asSeconds();
        activeBlock->update(playfield);
        playfield->updatePhysics();
        playfield->updateTimers(dt);
    }
    int line = playfield->clearLines();
    if (line > 0)
    {
        ui->addScore(line * 100);
    }

    if (playfield->checkGameOver() == true) 
    {
        currentState = GameState::GameOver; // Kill the game!
    }
}

void Game::render()
{
    window.clear(sf::Color(30,15,50));
    if (currentState == GameState::MainMenu)
    {
        ui->renderMainMenu(window);
    }
    else if (currentState == GameState::Playing) {
        ui->renderGameplayUI(window);
        playfield->draw(window);
        activeBlock->draw(window);
    }
    else if (currentState == GameState::GameOver) {
        // Just draw the Game Over screen!
        ui->renderGameOver(window); 
    }
    window.display();
}