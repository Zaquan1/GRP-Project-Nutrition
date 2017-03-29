#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "IntroState.h"
#include "StateMachine.h"

#include <SFML/Graphics/RenderWindow.hpp>

class Application
{
public:
	Application();

	void run();

private:
	StateMachine m_machine;
	sf::RenderWindow m_window;
};

#endif // APPLICATION_HPP