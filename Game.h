#ifndef GAME_H
#define GAME_H

#include "IGameObject.h"

class Game
{
public:
    Game();
    ~Game() = default;

    void run();
    void reset();

private:
    void const render();
    void update();
    void handleEvents(sf::Event& event);

	bool m_isPlaying;
    sf::Clock m_deltaTime;
    std::vector<IGameObject*> m_gameObjects;
    const sf::Vector2f m_windowResolution;
    const sf::VideoMode m_windowMode;
    const std::string m_windowTitel;
    const sf::Uint64 m_windowStyle;
    sf::RenderWindow m_window;

};

#endif //GAME_H