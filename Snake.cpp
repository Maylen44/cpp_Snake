#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Snake.h"

static const sf::Vector2f UpDirection(0.f, -20.f);
static const sf::Vector2f DownDirection(0.f, 20.f);
static const sf::Vector2f LeftDirection(-20.f, 0.f);
static const sf::Vector2f RightDirection(20.f, 0.f);

Snake::Snake()
    : m_size(sf::Vector2f(20.f, 20.f))
    , m_shape(m_size)
    , m_color(sf::Color::Green)
    , m_segments()
    , m_movementDirection(0.f, 0.f)
    , m_speedModificator(1.05f)
{
    m_shape.setFillColor(m_color);
    m_segments.push_back(m_shape);
}

void Snake::draw(sf::RenderWindow& window)
{
    for (const auto& object : m_segments)
    {
        window.draw(object);
    }
}

//
//Make better speedModificator calculation, without using bonus variables or what not
//
void Snake::update(sf::Clock& deltaTime)
{
    float speedFactor = m_speedModificator * m_segments.size() / 2;
    sf::Time elapsed = deltaTime.getElapsedTime();

    if (elapsed > sf::seconds(0.35f) / speedFactor)
    {
        m_segments.back().setPosition(m_segments.front().getPosition() + m_movementDirection);
        std::rotate(m_segments.begin(), m_segments.end() - 1, m_segments.end());
        deltaTime.restart();
    }
}

void Snake::handleEvents(sf::Event& event)
{
    if (event.type == Keyrelease)
    {
        switch (event.key.code)
        {
        case Up:
            if (m_movementDirection != DownDirection)
            {
                m_movementDirection = UpDirection;
            }
            break;
        case W:
            if (m_movementDirection != DownDirection)
            {
                m_movementDirection = UpDirection;
            }
            break;
        case Down:
            if (m_movementDirection != UpDirection)
            {
                m_movementDirection = DownDirection;
            }
            break;
        case S:
            if (m_movementDirection != UpDirection)
            {
                m_movementDirection = DownDirection;
            }
            break;
        case Left:
            if (m_movementDirection != RightDirection)
            {
                m_movementDirection = LeftDirection;
            }
            break;
        case A:
            if (m_movementDirection != RightDirection)
            {
                m_movementDirection = LeftDirection;
            }
            break;
        case Right:
            if (m_movementDirection != LeftDirection)
            {
                m_movementDirection = RightDirection;
            }
            break;
        case D:
            if (m_movementDirection != LeftDirection)
            {
                m_movementDirection = RightDirection;
            }
            break;
        default:
            m_movementDirection;
            break;
        }
    }
}

void Snake::reset(const sf::Vector2f& boundaries)
{
    m_segments.clear();
    m_segments.push_back(m_shape);
    m_segments.front().setPosition(boundaries.x / 2.f, boundaries.y / 2.f);
}

sf::Shape& Snake::getShape()
{
    return m_shape;
}

bool Snake::checkCollisionWith(IGameObject* object)
{
    return m_segments.front().getGlobalBounds().intersects(object->getShape().getGlobalBounds());
}

bool Snake::checkCollisionWith(const sf::Vector2f& boundaries)
{
    sf::Vector2f position = m_segments.front().getPosition();
    if (position.x < 0.f || position.x > boundaries.x ||
        position.y < 0.f || position.y > boundaries.y)
    {
        return true;
    }
    for (int i = 1; i < m_segments.size(); ++i)
    {
        if (m_segments.front().getGlobalBounds().intersects(m_segments[i].getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}

void Snake::addNewSegment()
{
    sf::RectangleShape newSegment(m_size);
    newSegment.setFillColor(m_color);
    newSegment.setPosition(m_segments.back().getPosition() - m_movementDirection);
    m_segments.push_back(newSegment);
}
