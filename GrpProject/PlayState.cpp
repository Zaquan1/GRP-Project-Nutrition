#include <memory>
#include <iostream>

#include "StateMachine.h"
#include "PlayState.h"
#include "MenuState.h"
#include "PeopleManager.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

PlayState::PlayState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace }, airPainter()
{
	//m_bgTex.loadFromFile("img/play.png");

	//m_bg.setTexture(m_bgTex, true);
	PeopleManager manager;
	manager.testPurpose();

	std::cout << "PlayState Init" << std::endl;
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
	sf::Event event;

	airPainter.run();
	MattoSprite();
	
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
			case sf::Keyboard::C:
				airPainter.ChangeDetect();

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
	sf::Image test;
	sf::Texture tex;
	sf::Sprite temp;
	cv::Mat tempMat;
	tempMat = airPainter.getCanvas();
	test.create(tempMat.cols/2, tempMat.rows/2, sf::Color(0, 200, 0, 255));
	tex.loadFromImage(test);
	
	temp.setTexture(tex, true);

	m_window.clear();
	m_window.draw(temp);
	m_window.draw(m_bg);
	m_window.display();
}