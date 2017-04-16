#include "Application.h"
#include <iostream>

Application::Application()
{
	m_window.setFramerateLimit(30);
}

void Application::run()
{
	// Create render window
	m_window.create(sf::VideoMode{ 1280, 720 }, "NutriGame", sf::Style::Titlebar | sf::Style::Close);

	// Initialize the engine
	m_machine.run(StateMachine::build<IntroState>(m_machine, m_window, true));

	sf::Clock clock;

	// Main loop
	while (m_machine.running())
	{
		m_machine.nextState();
		m_machine.update();
		m_machine.draw();

		sf::Time time = clock.getElapsedTime();
		//std::cout << 1.0f / time.asSeconds() << std::endl;
		clock.restart().asSeconds();
	}

	// Leaving the scope of 'Application' will cleanup the engine
}