#include "StateMachine.h"
#include "EndState.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "Application.h"

#include <memory>
#include <iostream>
string EndState::intToString(int number) {

	std::stringstream ss;
	ss << number;
	return ss.str();
}

EndState::EndState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace }
{
	m_bgTex.loadFromFile("img/end.png");

	m_bg.setTexture(m_bgTex, true);

	font.loadFromFile("arial.ttf");

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

	if (difftime(endT, beginT) < 1.0f)
	{
		endT = time(NULL);
	}
	else
	{
		beginT = time(NULL);
		endT = time(NULL);
		std::cout << time_f << std::endl;
		time_f += 1;
	}

	if (time_f == 3)
	{
		m_machine.lastState();
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
	drawInfo();
	m_window.display();
}

void EndState::drawInfo()
{
	//name, age gender job illness
	sf::Text info;
	info.setFont(font);

	info.setString("Person Status");
	info.setPosition(sf::Vector2f(60, 10));
	m_window.draw(info);

	info.setString("Name: " + person.getName());
	info.setPosition(sf::Vector2f(10, 110));
	m_window.draw(info);
	info.setString("Age: " + person.getAge());
	info.setPosition(sf::Vector2f(10, 210));
	m_window.draw(info);
	info.setString("Gender: " + person.getGender());
	info.setPosition(sf::Vector2f(10, 310));
	m_window.draw(info);
	info.setString("Job: " + person.getJob());
	info.setPosition(sf::Vector2f(10, 410));
	m_window.draw(info);
	info.setString("Illness: " + person.getIllness());
	info.setPosition(sf::Vector2f(10, 510));
	m_window.draw(info);

	info.setString("Your guess");
	info.setPosition(sf::Vector2f(550, 10));
	m_window.draw(info);

	string str;
	str = intToString((int)objects.at(1).getArea());
	info.setString("Carbohydrates: " + str + "%");
	info.setPosition(sf::Vector2f(500, 110));
	m_window.draw(info);

	str = intToString((int)objects.at(0).getArea());
	info.setString("Protein: " + str + "%");
	info.setPosition(sf::Vector2f(500, 210));
	m_window.draw(info);
	
	str = intToString((int)objects.at(3).getArea());
	info.setString("Fats: " + str + "%");
	info.setPosition(sf::Vector2f(500, 310));
	m_window.draw(info);

	str = intToString((int)objects.at(2).getArea());
	info.setString("Fibre: " + str + "%");
	info.setPosition(sf::Vector2f(500, 410));
	m_window.draw(info);

	info.setString("Result");
	info.setPosition(sf::Vector2f(1050, 10));
	m_window.draw(info);

	info.setString(checkResult((int)objects.at(1).getArea(), person.getCarbs()));
	info.setPosition(sf::Vector2f(1000, 110));
	m_window.draw(info);

	info.setString(checkResult((int)objects.at(0).getArea(), person.getProtein()));
	info.setPosition(sf::Vector2f(1000, 210));
	m_window.draw(info);

	info.setString(checkResult((int)objects.at(3).getArea(), person.getFats()));
	info.setPosition(sf::Vector2f(1000, 310));
	m_window.draw(info);

	info.setString(checkResult((int)objects.at(2).getArea(), person.getFibre()));
	info.setPosition(sf::Vector2f(1000, 410));
	m_window.draw(info);


}

string EndState::checkResult(int user, int actual)
{
	int range = user - actual;
	if (range > -5 && range < 5)
	{
		return "Good job!";
	}
	else if (range > 0)
	{
		if (range < 15)
		{
			return "It's a bit too much";
		}
		else
		{
			return "It's way too much!";
		}
	}
	else
	{
		if (range > -15)
		{
			return "It's a bit too little";
		}
		else
		{
			return "It's way too little";
		}
	}
}

