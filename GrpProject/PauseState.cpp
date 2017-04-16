#include "StateMachine.h"
#include "PauseState.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>
#include <iostream>

PauseState::PauseState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace }
{
	m_bgTex.loadFromFile("img/pause.png");

	m_bg.setTexture(m_bgTex, true);

	font.loadFromFile("arial.ttf");

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Resume");
	menu[0].setPosition(sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 1));
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2.0f, menu[0].getLocalBounds().height / 2.0f);

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Exit Game");
	menu[1].setPosition(sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 2));
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2.0f, menu[1].getLocalBounds().height / 2.0f);

	selectedItemIndex = 0;

	std::cout << "MenuState Init" << std::endl;
}

void PauseState::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void PauseState::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void PauseState::pause()
{
	std::cout << "MenuState Pause" << std::endl;
}

void PauseState::resume()
{
	std::cout << "MenuState Resume" << std::endl;
}

void PauseState::update()
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

			case sf::Keyboard::Up:
				MoveUp();
				break;

			case sf::Keyboard::Down:
				MoveDown();
				break;

			case sf::Keyboard::Return:
				switch (GetPressedItem())
				{
				case 0:
					m_machine.lastState();
					break;

				case 1:
					m_machine.quit();
					break;
				}

			default:
				break;
			}
			break;

		default:
			break;
		}
	}
}

void PauseState::draw()
{
	// Clear the previous drawing
	m_window.clear();
	m_window.draw(m_bg);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		m_window.draw(menu[i]);
	}

	
	m_window.display();
}