#include <memory>
#include <iostream>

#include "StateMachine.h"
#include "HelpState.h"
#include "Application.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

HelpState::HelpState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace }
{
	m_bgTex.loadFromFile("img/help.png");
	m_bg.setTexture(m_bgTex, true);

	std::cout << "HelpState Init" << std::endl;
}

void HelpState::update()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_machine.quit();
			break;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{

			case sf::Keyboard::BackSpace:
				m_next = StateMachine::build<IntroState>(m_machine, m_window, false);
				//m_machine.lastState();
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
	}
}

void HelpState::pause()
{
	std::cout << "IntroState Pause" << std::endl;
}

void HelpState::resume()
{
	std::cout << "IntroState Resume" << std::endl;
}

void HelpState::draw()
{
	// Clear the previous drawing
	m_window.clear();

	m_window.draw(m_bg);
	m_window.display();
}