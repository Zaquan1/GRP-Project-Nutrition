#include "StateMachine.h"
#include "EndState.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "Application.h"

#include <memory>
#include <iostream>

EndState::EndState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace }
{
	m_bgTex.loadFromFile("img/end.png");

	m_bg.setTexture(m_bgTex, true);

	std::cout << "EndState Init" << std::endl;
	
}

EndState::EndState(StateMachine& machine, sf::RenderWindow& window, bool replace, People p, vector<Object> o)
	:EndState(machine, window, replace)
{
	objects = o;
	person = p;
	person.status();
	for (int i = 0; i < objects.size(); i++)
		cout << objects.at(i).getArea();
}


void EndState::pause()
{
	std::cout << "EndState Pause" << std::endl;
}

void EndState::resume()
{
	std::cout << "EndState Resume" << std::endl;
}

void EndState::update()
{
	//people.status();
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

			case sf::Keyboard::Return:
				//m_machine.lastState(2);
				m_next = StateMachine::build<IntroState>(m_machine, m_window, false);
				break;

			case sf::Keyboard::Escape:
				m_machine.quit();
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

void EndState::draw()
{
	// Clear the previous drawing
	m_window.clear();
	m_window.draw(m_bg);

	m_window.display();
}