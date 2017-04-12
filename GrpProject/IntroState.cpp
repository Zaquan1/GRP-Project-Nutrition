#include "IntroState.h"
#include "PlayState.h"
#include "HelpState.h"
#include "AddState.h"
#include "StateMachine.h"


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <memory>

IntroState::IntroState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace }
{
	m_bgTex.loadFromFile("img/Intro_Background.png");
	m_bg.setTexture(m_bgTex, true);

	if (!font.loadFromFile("arial.ttf"))
	{
		//handle error
	}

	title.setFont(font);
	title.setFillColor(sf::Color::White);
	title.setString("NUTRIGAME");
	title.setPosition(sf::Vector2f(m_window.getSize().x / 2, 40));
	title.setOrigin(title.getLocalBounds().width / 2.0f, title.getLocalBounds().height / 2.0f);


	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 1));
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2.0f, menu[0].getLocalBounds().height / 2.0f);

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Help");
	menu[1].setPosition(sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 2));
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2.0f, menu[1].getLocalBounds().height / 2.0f);

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Add Character");
	menu[2].setPosition(sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	menu[2].setOrigin(menu[2].getLocalBounds().width / 2.0f, menu[2].getLocalBounds().height / 2.0f);

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setPosition(sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 4));
	menu[3].setOrigin(menu[3].getLocalBounds().width / 2.0f, menu[3].getLocalBounds().height / 2.0f);

	selectedItemIndex = 0;


	// Start off opaque
	m_alpha = sf::Color{ 0, 0, 0, 255 };

	// Fill the fader surface with black
	m_fader.setFillColor(m_alpha);
	m_fader.setSize(static_cast<sf::Vector2f>(m_bgTex.getSize()));

	std::cout << "IntroState Init" << std::endl;
}

void IntroState::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void IntroState::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void IntroState::pause()
{
	std::cout << "IntroState Pause" << std::endl;
}

void IntroState::resume()
{
	std::cout << "IntroState Resume" << std::endl;
}

void IntroState::update()
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
		{
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
					m_next = StateMachine::build<PlayState>(m_machine, m_window, true);
					break;

				case 1:
					m_next = StateMachine::build<HelpState>(m_machine, m_window, true);
					break;

				case 2:
					m_next = StateMachine::build<AddState>(m_machine, m_window, true);
					break;

				case 3:
					m_machine.quit();
					break;
				}


			default:
				break;
			}
			break;
		}

		default:
			break;
		}
	}

	if (m_alpha.a != 0)
		m_alpha.a--;

	m_fader.setFillColor(m_alpha);
}

void IntroState::draw()
{
	// Clear the previous drawing
	m_window.clear();

	m_window.draw(m_bg);

	m_window.draw(title);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		m_window.draw(menu[i]);
	}
	

	// No need to draw if it's transparent
	if (m_alpha.a != 0)
		m_window.draw(m_fader);

	m_window.display();
}