#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "State.h"
#include "AirPainter.h"
#include "PeopleManager.h"
#include <ctime>
#include <SFML\Graphics.hpp>
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

	void MattoSprite();
	void drawInfo();
	sf::Texture m_bgTex;
	sf::Texture aP_Tex;
	sf::Sprite m_bg;
	sf::Sprite aP;
	sf::Font font;
	sf::Text time_text;
	sf::FloatRect textRect;

	time_t beginT = NULL;
	time_t endT = NULL;
	int time_f = 0;
	std::string timer;

	AirPainter airPainter;
	PeopleManager pManager;
};

#endif // PLAYSTATE_HPP