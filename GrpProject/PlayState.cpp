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
	m_bgTex.loadFromFile("img/play.png");

	m_bg.setTexture(m_bgTex, true);

	font.loadFromFile("arial.ttf");
	time_text.setFont(font);

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
		time_text.setString(std::to_string(time_f));
		textRect = time_text.getLocalBounds();
		time_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		time_text.setPosition(sf::Vector2f(840, 689));
		//std::cout << time_f << std::endl;
		time_f += 1;
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
	if (!aP_Tex.loadFromImage(image))
	{
		cout << "error loading image to texture" << endl;
	}
	aP.setTexture(aP_Tex, true);
}

void PlayState::draw()
{
	// Clear the previous drawing
	m_window.clear();
	m_window.draw(m_bg);
	m_window.draw(time_text);
	drawInfo();
	m_window.draw(aP);
	m_window.display();
}

void PlayState::drawInfo()
{
	sf::Text info;
	info.setFont(font);
	info.setString(airPainter.getColorArea("red"));
	info.setPosition(sf::Vector2f(1010, 175));
	m_window.draw(info);

}