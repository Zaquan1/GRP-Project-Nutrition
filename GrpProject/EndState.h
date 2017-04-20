#ifndef ENDSTATE_HPP
#define ENDSTATE_HPP

#include "State.h"
#include <sstream>
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

	EndState(StateMachine& machine, sf::RenderWindow& window, bool replace, People p, vector<Object> o, int left);

	void pause();
	void resume();

	void update();
	void draw();
	void drawInfo();

private:
	sf::Texture m_bgTex;
	sf::Sprite m_bg;
	sf::Font font;

	time_t beginT = time(NULL);
	time_t endT = time(NULL);
	std::string timer;
	int time_f = 0;
	int left;

	People person;
	vector<Object> objects;

	string intToString(int number);
	string checkResult(int user, int actual);
};

#endif // ENDSTATE_HPP