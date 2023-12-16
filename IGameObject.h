#ifndef I_GAME_OBJECT_H
#define I_GAME_OBJECT_H

#include <SFML/Graphics.hpp>

enum Event
{
	Keyrelease = sf::Event::KeyReleased,
	Closed = sf::Event::Closed,

	Up = sf::Keyboard::Up,
	W = sf::Keyboard::W,
	Down = sf::Keyboard::Down,
	S = sf::Keyboard::S,
	Left = sf::Keyboard::Left,
	A = sf::Keyboard::A,
	Right = sf::Keyboard::Right,
	D = sf::Keyboard::D,

	ESC = sf::Keyboard::Escape,
	R = sf::Keyboard::R
};

class IGameObject
{
public:
	IGameObject() = default;
	virtual ~IGameObject() = default;

	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void update(sf::Clock& deltaTime) = 0;
	virtual void handleEvents(sf::Event& event) = 0;
	virtual void reset(const sf::Vector2f& boundaries) = 0;
	virtual sf::Shape& getShape() = 0;
};
#endif //I_GAME_OBJECT_H
