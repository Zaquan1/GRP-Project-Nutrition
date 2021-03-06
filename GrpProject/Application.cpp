#include "Application.h"

Application::Application()
{
	m_window.setFramerateLimit(30);
}

void Application::run()
{
	// Create render window
	m_window.create(sf::VideoMode{ 1280, 720 }, "NutriFill", sf::Style::Titlebar | sf::Style::Close);

	// Initialize the engine
	m_machine.run(StateMachine::build<IntroState>(m_machine, m_window, true));

	// Main loop
	while (m_machine.running())
	{
		m_machine.nextState();
		m_machine.update();
		m_machine.draw();
	}

	// Leaving the scope of 'Application' will cleanup the engine
}