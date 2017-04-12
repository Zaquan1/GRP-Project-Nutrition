#include <memory>
#include <iostream>

#include "StateMachine.h"
#include "AddState.h"
#include "Application.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

AddState::AddState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace }
{
	m_bgTex.loadFromFile("img/Add.png");
	m_bg.setTexture(m_bgTex, true);

	gui.setWindow(m_window);

	try
	{
		// Load the widgets
		loadWidgets(gui);
	}
	catch (const tgui::Exception& e)
	{
		std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
	}

	std::cout << "AddState Init" << std::endl;
}

void AddState::submit(tgui::EditBox::Ptr First, tgui::EditBox::Ptr Last, tgui::EditBox::Ptr Gender, tgui::EditBox::Ptr Illness,
					  tgui::EditBox::Ptr Job, tgui::EditBox::Ptr Carbs, tgui::EditBox::Ptr Fats, tgui::EditBox::Ptr Protein,
					  tgui::EditBox::Ptr Fiber)
{
	std::ofstream myfile("people.txt", std::ios::app);

	if (myfile.is_open())
	{
		myfile << "*" << std::endl;
		myfile << First->getText().toAnsiString() << std::endl;
		myfile << Last->getText().toAnsiString() << std::endl;
		myfile << Gender->getText().toAnsiString() << std::endl;
		myfile << Job->getText().toAnsiString() << std::endl;
		myfile << Illness->getText().toAnsiString() << std::endl;
		myfile << Carbs->getText().toAnsiString() << std::endl;
		myfile << Fats->getText().toAnsiString() << std::endl;
		myfile << Protein->getText().toAnsiString() << std::endl;
		myfile << Fiber->getText().toAnsiString() << std::endl;

		myfile.close();
	}
	else std::cout << "Unable to open file";

	std::cout << "First Name: " << First->getText().toAnsiString() << std::endl;
	std::cout << "Age: " << Last->getText().toAnsiString() << std::endl;
	std::cout << "Gender: " << Gender->getText().toAnsiString() << std::endl;
	std::cout << "Job: " << Job->getText().toAnsiString() << std::endl;
	std::cout << "Illness: " << Illness->getText().toAnsiString() << std::endl;
	std::cout << "Carbs: " << Carbs->getText().toAnsiString() << std::endl;
	std::cout << "Fats: " << Fats->getText().toAnsiString() << std::endl;
	std::cout << "Protein: " << Protein->getText().toAnsiString() << std::endl;
	std::cout << "Fiber: " << Fiber->getText().toAnsiString() << std::endl;

}

void AddState::loadWidgets(tgui::Gui& gui)
{
	auto theme = tgui::Theme::create("Black.txt");

	auto windowWidth = tgui::bindWidth(gui);
	auto windowHeight = tgui::bindHeight(gui);

	tgui::EditBox::Ptr editBoxName = theme->load("EditBox");
	editBoxName->setSize(200, 40);
	editBoxName->setPosition(50, 50);
	editBoxName->setDefaultText("Name");
	gui.add(editBoxName, "Name");


	tgui::EditBox::Ptr editBoxAge = theme->load("EditBox");
	editBoxAge->setSize(200, 40);
	editBoxAge->setPosition(50, 100);
	editBoxAge->setTextSize(0);
	editBoxAge->setDefaultText("Age");
	gui.add(editBoxAge, "Age");

	tgui::EditBox::Ptr editBoxGender = theme->load("EditBox");
	editBoxGender->setSize(200, 40);
	editBoxGender->setPosition(50, 150);
	editBoxGender->setTextSize(0);
	editBoxGender->setDefaultText("Gender");
	gui.add(editBoxGender, "Gender");

	tgui::EditBox::Ptr editBoxJob = theme->load("EditBox");
	editBoxJob->setSize(200, 40);
	editBoxJob->setPosition(50, 200);
	editBoxJob->setTextSize(0);
	editBoxJob->setDefaultText("Job");
	gui.add(editBoxJob, "Job");

	tgui::EditBox::Ptr editBoxIllness = theme->load("EditBox");
	editBoxIllness->setSize(200, 40);
	editBoxIllness->setPosition(50, 250);
	editBoxIllness->setTextSize(0);
	editBoxIllness->setDefaultText("Illness");
	gui.add(editBoxIllness, "Illness");


	tgui::EditBox::Ptr editBoxCarbs = theme->load("EditBox");
	editBoxCarbs->setSize(200, 40);
	editBoxCarbs->setPosition(300, 100);
	editBoxCarbs->setTextSize(0);
	editBoxCarbs->setDefaultText("Carbohydrates");
	gui.add(editBoxCarbs, "Carbohydrates");

	tgui::EditBox::Ptr editBoxFats = theme->load("EditBox");
	editBoxFats->setSize(200, 40);
	editBoxFats->setPosition(300, 150);
	editBoxFats->setTextSize(0);
	editBoxFats->setDefaultText("Fats");
	gui.add(editBoxFats, "Fats");

	tgui::EditBox::Ptr editBoxProtein = theme->load("EditBox");
	editBoxProtein->setSize(200, 40);
	editBoxProtein->setPosition(300, 200);
	editBoxProtein->setTextSize(0);
	editBoxProtein->setDefaultText("Protein");
	gui.add(editBoxProtein, "Protein");

	tgui::EditBox::Ptr editBoxFiber = theme->load("EditBox");
	editBoxFiber->setSize(200, 40);
	editBoxFiber->setPosition(300, 250);
	editBoxFiber->setTextSize(0);
	editBoxFiber->setDefaultText("Fiber");
	gui.add(editBoxFiber, "Fiber");

	tgui::Button::Ptr button = theme->load("Button");
	button->setSize(windowWidth / 2, windowHeight / 6);
	button->setPosition(windowWidth / 4, windowHeight * 7 / 10);
	button->setText("Submit");
	gui.add(button);

	button->connect("pressed", &AddState::submit, this, editBoxName, editBoxAge, editBoxGender, editBoxIllness, editBoxJob,
														editBoxCarbs, editBoxFats, editBoxProtein, editBoxFiber);
	
}


void AddState::update()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_machine.quit();
			break;

		case sf::Event::Resized:
			m_window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
			gui.setView(m_window.getView());

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{

			case sf::Keyboard::Escape:
				m_next = StateMachine::build<IntroState>(m_machine, m_window, false);
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}

		gui.handleEvent(event);
	}
}

void AddState::pause()
{
	std::cout << "IntroState Pause" << std::endl;
}

void AddState::resume()
{
	std::cout << "IntroState Resume" << std::endl;
}

void AddState::draw()
{
	// Clear the previous drawing
	m_window.clear();

	//m_window.draw(m_bg);
	gui.draw();
	
	m_window.display();
}