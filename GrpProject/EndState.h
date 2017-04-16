#ifndef ENDSTATE_HPP
#define ENDSTATE_HPP

#include "State.h"

#include "SFML\Graphics.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "People.h"
#include "Object.h"

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class EndState : public State
{
public:
	EndState(StateMachine& machine, sf::RenderWindow& window, bool replace = false);

	EndState(StateMachine& machine, sf::RenderWindow& window, bool replace, People p, vector<Object> o);

	void pause();
	void resume();

	void update();
	void draw();

private:
	sf::Texture m_bgTex;
	sf::Sprite m_bg;

	People person;
	vector<Object> objects;

};

#endif // ENDSTATE_HPP