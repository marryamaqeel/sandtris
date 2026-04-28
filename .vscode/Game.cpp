#include "Game.hpp"
#include<SFML/Graphics.hpp>

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
        activeBlock->update(playfield);
        playfield->updatePhysics();
    }
    int line = playfield->clearLines();
    if (line > 0)
    {
        ui->addScore(line * 100);
    }
}

void Game::render()
{
    window.clear(sf::Color(30,15,50));
    if (currentState == GameState::MainMenu)
    {
        ui->renderMainMenu(window);
    }
    if (currentState == GameState::Playing)
    {
        playfield->draw(window);
        activeBlock->draw(window);
        ui->renderGameplayUI(window);
    }
    window.display();
}