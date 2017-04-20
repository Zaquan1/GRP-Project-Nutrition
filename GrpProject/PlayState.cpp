#include <memory>
#include <iostream>

#include "StateMachine.h"
#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"
#include "IntroState.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

PlayState::PlayState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace }, airPainter(m_window.getSize().x, m_window.getSize().y), pManager()
{
	m_bgTex.loadFromFile("img/play.png");

	m_bg.setTexture(m_bgTex, true);

	font.loadFromFile("arial.ttf");
	time_text.setFont(font);
	modeChange = true;
	reset = false;
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
	if (reset)
	{
		airPainter.resetArea_Canvas();
		pManager.removePeople();
		time_f = 0;
		reset = false;
	}
	cout << pManager.peopleLeft() << endl;
	if (pManager.peopleLeft() == 0)
	{
		pause();
		m_next = StateMachine::build<IntroState>(m_machine, m_window, false);
	}
	else
	{
		airPainter.run();
		MattoSprite();

		if (difftime(endT, beginT) < 1.0f)
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


			std::cout << time_f << std::endl;
			time_f += 1;
		}
		if (time_f < 2)
		{
			airPainter.setIgnore(false);
		}
		else
		{
			airPainter.setIgnore(true);
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

				case sf::Keyboard::P:
					m_next = StateMachine::build<PauseState>(m_machine, m_window, false);
					break;

				case sf::Keyboard::C:
					airPainter.ChangeDetect();
					modeChange = !modeChange;
					break;
				default:
					break;
				}
				break;

			default:
				break;
			}
		}

		if (time_f > 60)
		{
			m_next = StateMachine::build<EndState>(new EndState(m_machine, m_window, false, pManager.getPeople(), airPainter.getAllColor(), pManager.peopleLeft()));
			reset = true;
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
	info.setString(airPainter.getColorArea("red") + "%");
	info.setPosition(sf::Vector2f(1010, 175));
	m_window.draw(info);
	info.setString(airPainter.getColorArea("green") + "%");
	info.setPosition(sf::Vector2f(1175, 175));
	m_window.draw(info);
	info.setString(airPainter.getColorArea("blue") + "%");
	info.setPosition(sf::Vector2f(1010, 260));
	m_window.draw(info);
	info.setString(airPainter.getColorArea("yellow") + "%");
	info.setPosition(sf::Vector2f(1175, 260));
	m_window.draw(info);

	info.setString(pManager.getPeople().getName());
	info.setPosition(sf::Vector2f(1065, 415));
	m_window.draw(info);
	info.setString(pManager.getPeople().getAge());
	info.setPosition(sf::Vector2f(1065, 465));
	m_window.draw(info);
	info.setString(pManager.getPeople().getGender());
	info.setPosition(sf::Vector2f(1065, 520));
	m_window.draw(info);
	info.setString(pManager.getPeople().getJob());
	info.setPosition(sf::Vector2f(1065, 570));
	m_window.draw(info);
	info.setString(pManager.getPeople().getIllness());
	info.setPosition(sf::Vector2f(1065, 625));
	m_window.draw(info);

	info.setString("C to change filter mode: ");
	info.setPosition(sf::Vector2f(10, 685));
	m_window.draw(info);
	if (modeChange)
	{
		info.setString("Circle Detect");
	}
	else
	{
		info.setString("Color Detect");
	}
	info.setPosition(sf::Vector2f(340, 685));
	m_window.draw(info);
}