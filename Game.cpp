#include "Game.hpp"
#include<SFML/Graphics.hpp>

sf::Clock deltaClock;


Game::Game() : window(sf::VideoMode({800,600}), "SandTris")
{
    window.setFramerateLimit(60); 
    playfield = new grid(150,125);
    currentDifficulty = 2;
    activeBlock = new Tetromino(currentDifficulty);
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
            if (const auto* mouseBtn = event->getIf<sf::Event::MouseButtonPressed>()) 
            {
                if (mouseBtn->button == sf::Mouse::Button::Left) 
                {
                    // Pass the mouse position to the UI
                    int diff = ui->handleMenuClick(mouseBtn->position);
                    
                    if (diff > 0) // If they clicked a valid button!
                    {
                        currentDifficulty = diff;
                        ui->updateHighScoreDisplay(currentDifficulty);
                        
                        // Delete the old block and spawn a NEW one with the correct difficulty!
                        delete activeBlock;
                        activeBlock = new Tetromino(currentDifficulty);
                        
                        deltaClock.restart();
                        currentState = GameState::Playing;
                    }
                }
            }
        }

        else if (currentState == GameState::Playing)
        {
            if (event->is<sf::Event::KeyPressed>())
            {
                const auto* key = event->getIf<sf::Event::KeyPressed>();

                if (key->code == sf::Keyboard::Key::Escape)
                {
                    currentState = GameState::Paused;
                }
            }

            activeBlock->handleInput(event.value(),playfield);
        }

        else if(currentState == GameState::Paused)
        {
            if (event->is<sf::Event::KeyPressed>()) {
                const auto* key = event->getIf<sf::Event::KeyPressed>();
                if (key->code == sf::Keyboard::Key::Escape) {
                    deltaClock.restart();
                    currentState = GameState::Playing;
                }
            }
        }

        else if (currentState == GameState::GameOver)
        {
            if (event->is<sf::Event::KeyPressed>())
            {
                const auto* key = event->getIf<sf::Event::KeyPressed>();

                if (key->code == sf::Keyboard::Key::Enter)
                {
                    delete playfield;
                    delete activeBlock;
                    playfield = new grid(150,125);
                    activeBlock = new Tetromino(currentDifficulty);
                    ui->resetScore();

                    currentState = GameState::Playing;
                }
                else if (key->code == sf::Keyboard::Key::Escape) {
                    // GO BACK TO MAIN MENU!
                    delete playfield; delete activeBlock;
                    playfield = new grid(150,125);
                    activeBlock = new Tetromino(currentDifficulty);
                    ui->resetScore();
                    currentState = GameState::MainMenu; // Switch state!
                }
            }
            
        }
    }
    
}

void Game::update()
{
    if(currentState == GameState::Playing)
    {
        float dt = deltaClock.restart().asSeconds();
        activeBlock->update(playfield,currentDifficulty);
        playfield->updatePhysics();
        playfield->updateTimers(dt);
    
        int line = playfield->clearLines();
        if (line > 0)
        {
            ui->addScore(line * 10, currentDifficulty);
        }

        if (playfield->checkGameOver() == true) 
        {
            ui->saveHighScore(currentDifficulty);
            currentState = GameState::GameOver;
        }
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
    else if (currentState == GameState::Paused)
    {
        ui->renderGameplayUI(window);
        playfield->draw(window);
        activeBlock->draw(window);
        ui->renderPause(window);
    }
    else if (currentState == GameState::GameOver) {
        ui->renderGameOver(window,currentDifficulty); 
    }
    window.display();
}
