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

	font.loadFromFile("arial.ttf");


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

void AddState::submit(tgui::EditBox::Ptr First, tgui::EditBox::Ptr Age, tgui::EditBox::Ptr Gender, tgui::EditBox::Ptr Illness,
	tgui::EditBox::Ptr Job, tgui::EditBox::Ptr Carbs, tgui::EditBox::Ptr Fats, tgui::EditBox::Ptr Protein,
	tgui::EditBox::Ptr Fiber)
{


	v_words.clear();
	v_words.push_back(First->getText().toAnsiString());
	v_words.push_back(Gender->getText().toAnsiString());
	v_words.push_back(Job->getText().toAnsiString());
	v_words.push_back(Illness->getText().toAnsiString());

	v_nums.clear();
	v_nums.push_back(Age->getText().toAnsiString());
	v_nums.push_back(Carbs->getText().toAnsiString());
	v_nums.push_back(Fats->getText().toAnsiString());
	v_nums.push_back(Protein->getText().toAnsiString());
	v_nums.push_back(Fiber->getText().toAnsiString());

	isNumber(v_nums);
	isWord(v_words);
	isValid();

	setErrorTextStyle();

	std::ofstream myfile("record.txt", std::ios::app);
	if (all_words_valid && all_num_valid)
	{
		if (myfile.is_open())
		{
			myfile << "*" << std::endl;
			myfile << First->getText().toAnsiString() << std::endl;
			myfile << Age->getText().toAnsiString() << std::endl;
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
	}
	else errorPrint();
}

void AddState::loadWidgets(tgui::Gui& gui)
{
	auto theme = tgui::Theme::create("Black.txt");

	auto windowWidth = tgui::bindWidth(gui);
	auto windowHeight = tgui::bindHeight(gui);

	tgui::EditBox::Ptr editBoxName = theme->load("EditBox");
	editBoxName->setSize(200, 40);
	editBoxName->setPosition(200, 100);
	editBoxName->setDefaultText("Name");
	gui.add(editBoxName, "Name");


	tgui::EditBox::Ptr editBoxAge = theme->load("EditBox");
	editBoxAge->setSize(200, 40);
	editBoxAge->setPosition(200, 150);
	editBoxAge->setTextSize(0);
	editBoxAge->setDefaultText("Age");
	gui.add(editBoxAge, "Age");

	tgui::EditBox::Ptr editBoxGender = theme->load("EditBox");
	editBoxGender->setSize(200, 40);
	editBoxGender->setPosition(200, 200);
	editBoxGender->setTextSize(0);
	editBoxGender->setDefaultText("Gender");
	gui.add(editBoxGender, "Gender");

	tgui::EditBox::Ptr editBoxJob = theme->load("EditBox");
	editBoxJob->setSize(200, 40);
	editBoxJob->setPosition(200, 250);
	editBoxJob->setTextSize(0);
	editBoxJob->setDefaultText("Job");
	gui.add(editBoxJob, "Job");

	tgui::EditBox::Ptr editBoxIllness = theme->load("EditBox");
	editBoxIllness->setSize(200, 40);
	editBoxIllness->setPosition(200, 300);
	editBoxIllness->setTextSize(0);
	editBoxIllness->setDefaultText("Illness");
	gui.add(editBoxIllness, "Illness");


	tgui::EditBox::Ptr editBoxCarbs = theme->load("EditBox");
	editBoxCarbs->setSize(200, 40);
	editBoxCarbs->setPosition(850, 150);
	editBoxCarbs->setTextSize(0);
	editBoxCarbs->setDefaultText("Carbohydrates");
	gui.add(editBoxCarbs, "Carbohydrates");

	tgui::EditBox::Ptr editBoxFats = theme->load("EditBox");
	editBoxFats->setSize(200, 40);
	editBoxFats->setPosition(850, 200);
	editBoxFats->setTextSize(0);
	editBoxFats->setDefaultText("Fats");
	gui.add(editBoxFats, "Fats");

	tgui::EditBox::Ptr editBoxProtein = theme->load("EditBox");
	editBoxProtein->setSize(200, 40);
	editBoxProtein->setPosition(850, 250);
	editBoxProtein->setTextSize(0);
	editBoxProtein->setDefaultText("Protein");
	gui.add(editBoxProtein, "Protein");

	tgui::EditBox::Ptr editBoxFiber = theme->load("EditBox");
	editBoxFiber->setSize(200, 40);
	editBoxFiber->setPosition(850, 300);
	editBoxFiber->setTextSize(0);
	editBoxFiber->setDefaultText("Fiber");
	gui.add(editBoxFiber, "Fiber");

	tgui::Button::Ptr button = theme->load("Button");
	button->setSize(windowWidth / 2, windowHeight / 6);
	button->setPosition(windowWidth / 4, windowHeight * 7.5 / 10);
	button->setText("Submit");
	gui.add(button);

	button->connect("pressed", &AddState::submit, this, editBoxName, editBoxAge, editBoxGender, editBoxIllness, editBoxJob,
		editBoxCarbs, editBoxFats, editBoxProtein, editBoxFiber);

}


void AddState::isNumber(std::vector <std::string> &num)
{
	for (int i = 0; i < 5; i++)
	{
		for (unsigned int j = 0; j < num[i].length(); j++)
		{
			if (!(num[i][j] > 47 && num[i][j] < 58))
			{
				num_flag[i] = false;
				std::cout << num[i].length() << std::endl;
			}
			else
			{
				num_flag[i] = true;
			}
		}
	}
}

void AddState::isWord(std::vector <std::string> &word)
{
	for (int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < word[i].length(); j++)
		{
			if (!(word[i][j] > 64 && word[i][j] < 91 || word[i][j] > 96 && word[i][j] < 123))
			{
				word_flag[i] = false;
			}
			else
			{
				word_flag[i] = true;
			}
		}
	}
}

void AddState::isValid()
{
	all_words_valid = true;
	all_num_valid = true;

	for (int i = 0; i < 5; i++)
	{
		if (num_flag[i] == false)
		{
			all_num_valid = false;
		}

	}

	for (int i = 0; i < 4; i++)
	{
		if (word_flag[i] == false)
		{
			all_words_valid = false;
		}
	}
}

void AddState::setErrorTextStyle()
{
	for (int i = 0; i < 9; i++)
	{
		error[i].setFont(font);
		error[i].setString("Invalid");
		error[i].setFillColor(sf::Color::Black);
		error[i].setCharacterSize(24);
		errTextRect = error[0].getLocalBounds();
		error[i].setOrigin(errTextRect.left + errTextRect.width / 2.0f, errTextRect.top + errTextRect.height / 2.0f);
	}

	error[0].setPosition(140, 120);
	error[1].setPosition(140, 220);
	error[2].setPosition(140, 270);
	error[3].setPosition(140, 320);
	error[4].setPosition(140, 170);
	error[5].setPosition(790, 170);
	error[6].setPosition(790, 220);
	error[7].setPosition(790, 270);
	error[8].setPosition(790, 320);
}

void AddState::errorPrint()
{
	for (int i = 0; i < 4; i++)
	{
		if (word_flag[i] == false)
		{
			switch (i)
			{
			case 0:
			{
				error[0].setFillColor(sf::Color::Red);
				break;
			}

			case 1:
			{
				error[1].setFillColor(sf::Color::Red);
				break;
			}

			case 2:
			{
				error[2].setFillColor(sf::Color::Red);
				break;
			}

			case 3:
			{
				error[3].setFillColor(sf::Color::Red);
				break;
			}

			default:
				break;
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (num_flag[i] == false)
		{
			switch (i)
			{
			case 0:
			{
				error[4].setFillColor(sf::Color::Red);
				break;
			}

			case 1:
			{
				error[5].setFillColor(sf::Color::Red);
				break;
			}

			case 2:
			{
				error[6].setFillColor(sf::Color::Red);
				break;
			}

			case 3:
			{
				error[7].setFillColor(sf::Color::Red);
				break;
			}

			case 4:
			{
				error[8].setFillColor(sf::Color::Red);
				break;
			}

			default:
				break;
			}
		}
	}
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

	m_window.draw(m_bg);
	gui.draw();

	for (int i = 0; i < 9; i++)
	{
		m_window.draw(error[i]);
	}

	m_window.display();
}