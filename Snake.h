#ifndef SNAKE_H
#define SNAKE_H

#include "IGameObject.h"

class Snake : public IGameObject
{
public:
	Snake();
	virtual ~Snake() = default;

	void draw(sf::RenderWindow& window) override;
	void update(sf::Clock& deltaTime) override;
	void handleEvents(sf::Event& event) override;
	void reset(const sf::Vector2f& boundaries) override;
	sf::Shape& getShape() override;
	bool checkCollisionWith(IGameObject* object);
	bool checkCollisionWith(const sf::Vector2f& boundaries);
	void addNewSegment();


private:
	sf::Vector2f m_size;
	sf::RectangleShape m_shape;
	sf::Color m_color;
	std::vector<sf::RectangleShape> m_segments;
	sf::Vector2f m_movementDirection;
	float m_speedModificator;
};

#endif //SNAKE_H