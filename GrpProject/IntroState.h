#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include "State.h"

#include <SFML\Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#define MAX_NUMBER_OF_ITEMS 4

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class IntroState : public State
{
public:
	IntroState(StateMachine& game, sf::RenderWindow& window, bool replace = true);

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

	sf::Texture m_helpTex;
	sf::Sprite m_help;

	bool help;

	int selectedItemIndex;
	sf::Font font;
	sf::Text title;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
};

#endif // INTROSTATE_HPP