#ifndef HELPSTATE_HPP
#define HELPSTATE_HPP

#include "State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


class StateMachine;

namespace sf
{
	class RenderWindow;
}


class HelpState : public State
{
public:
	HelpState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

	void pause();
	void resume();

	void update();
	void draw();

private:

	sf::Texture m_bgTex;
	sf::Sprite m_bg;

};

#endif // !HELPSTATE_HPP
