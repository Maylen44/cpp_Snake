#ifndef FOOD_H
#define FOOD_H

#include "IGameObject.h"

class Food : public IGameObject
{
public:
	Food();
	virtual ~Food() = default;

	void draw(sf::RenderWindow& window) override;
	void update(sf::Clock& deltaTime) override;
	void handleEvents(sf::Event& event) override;
	void reset(const sf::Vector2f& boundaries) override;
	sf::Shape& getShape() override;

private:
	const sf::Vector2f m_size;
	sf::RectangleShape m_shape;
	const sf::Color m_color;
};

#endif //FOOD_H