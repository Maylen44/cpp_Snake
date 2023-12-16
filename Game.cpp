#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Snake.h"
#include "Food.h"

static void clearObjects(std::vector<IGameObject*> gameObjects)
{
    for (auto& object : gameObjects)
    {
        delete object;
    }
    gameObjects.clear();
}

static bool checkingClossingGame(sf::Event& event)
{
    if ((event.type == Closed) ||
        ((event.type == Keyrelease) && (event.key.code == ESC)))
    {
        return true;
    }
    return false;
}

static bool checkingRestartGame(sf::Event& event)
{
    if ((event.type == Keyrelease) && (event.key.code == R))
    {
        return true;
    }
    return false;
}

Game::Game()
    : m_isPlaying(false)
    , m_deltaTime()
    , m_gameObjects()
    , m_windowResolution(800.f, 600.f)
    , m_windowMode(m_windowResolution.x, m_windowResolution.y)
    , m_windowTitel("SNAKE")
    , m_windowStyle(sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close)
    , m_window(m_windowMode, m_windowTitel, m_windowStyle)
{}

void Game::run()
{
    Snake* snake = new Snake();
    Food* food = new Food();

    m_gameObjects.push_back(snake);
    m_gameObjects.push_back(food);
    reset();
    m_isPlaying = true;

    while (m_isPlaying)
    {
        sf::Event event;

        while (m_window.pollEvent(event))
        {
            if (checkingClossingGame(event))
            {
                m_isPlaying = false;
            }
            else if(checkingRestartGame(event))
            {
                reset();
            }
        }
        if (m_isPlaying)
        {
            handleEvents(event);

            if (snake->checkCollisionWith(m_windowResolution))
            {
                reset();
            }
            else if (snake->checkCollisionWith(food))
            {
                snake->addNewSegment();
                food->reset(m_windowResolution);
            }
            update();
        }
        render();
    }

    clearObjects(m_gameObjects);
    m_window.close();
}

void const Game::render()
{
    m_window.clear();
    for (auto& object : m_gameObjects)
    {
        object->draw(m_window);
    }
    m_window.display();
}

void Game::update()
{
    for (auto& object : m_gameObjects)
    {
        object->update(m_deltaTime);
    }
}

void Game::handleEvents(sf::Event& event)
{
    for (auto& object : m_gameObjects)
    {
        object->handleEvents(event);
    }
}

void Game::reset()
{
    for (auto& object : m_gameObjects)
    {
        object->reset(m_windowResolution);
    }
}
