#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include "State.h"

#include "SFML\Graphics.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#define MAX_NUMBER_OF_ITEMS 2

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class PauseState : public State
{
public:
	PauseState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

	void pause();
	void resume();

	void update();
	void draw();

	void MoveUp();
	void MoveDown();

	int GetPressedItem() { return selectedItemIndex; }

private:
	sf::Texture m_bgTex;
	sf::Sprite m_bg;

	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

};

#endif // PAUSESTATE_HPP