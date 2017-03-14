#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "State.h"
#include "AirPainter.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class PlayState : public State
{
public:
	PlayState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

	void pause();
	void resume();

	void update();
	void draw();

private:
	sf::Texture m_bgTex;
	sf::Sprite m_bg;

	AirPainter airPainter;

	void MattoSprite();
};

#endif // PLAYSTATE_HPP