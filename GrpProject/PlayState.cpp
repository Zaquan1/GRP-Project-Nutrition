#include <memory>
#include <iostream>

#include "StateMachine.h"
#include "PlayState.h"
#include "MenuState.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

PlayState::PlayState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace }, airPainter(m_window.getSize().x, m_window.getSize().y), pManager()
{

	//m_bg.setTexture(m_bgTex, true);

	std::cout << "PlayState Init" << std::endl;
	pManager.testPurpose();
}

void PlayState::pause()
{
	std::cout << "PlayState Pause" << std::endl;
}

void PlayState::resume()
{
	std::cout << "PlayState Resume" << std::endl;
}

void PlayState::update()
{
	airPainter.run();
	MattoSprite();
	sf::Event event;
	if (difftime(endT, beginT) < 2.0f)
	{
		endT = time(NULL);
	}
	else
	{
		beginT = time(NULL);
		endT = time(NULL);

		std::cout << "Time" << std::endl;
	}

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
			case sf::Keyboard::Escape:
				m_machine.quit();
				break;

			case sf::Keyboard::M:
				m_next = StateMachine::build<MenuState>(m_machine, m_window, false);
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

void PlayState::MattoSprite()
{
	sf::Image image;
	cv::Mat tempMat;

	tempMat = airPainter.getCanvas();
	cv::cvtColor(tempMat, tempMat, cv::COLOR_BGR2RGBA);
	image.create(tempMat.cols, tempMat.rows, tempMat.ptr());
	image.createMaskFromColor(sf::Color::Black);
	if (!m_bgTex.loadFromImage(image))
	{
		cout << "error loading image to texture" << endl;
	}
	m_bg.setTexture(m_bgTex, true);
}

void PlayState::draw()
{
	// Clear the previous drawing
	m_window.clear();
	m_window.draw(m_bg);
	m_window.display();
}