#ifndef ADDSTATE_HPP
#define ADDSTATE_HPP

#include "State.h"
#include <iostream>
#include <fstream>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <TGUI\TGUI.hpp>


class StateMachine;

namespace sf
{
	class RenderWindow;
}

class AddState : public State
{
public:
	AddState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

	void pause();
	void resume();

	void submit(tgui::EditBox::Ptr First, tgui::EditBox::Ptr Last, tgui::EditBox::Ptr Gender, tgui::EditBox::Ptr Illness, 
				tgui::EditBox::Ptr Job, tgui::EditBox::Ptr Carbs, tgui::EditBox::Ptr Fats, tgui::EditBox::Ptr Protein, 
				tgui::EditBox::Ptr Fiber);
	void loadWidgets(tgui::Gui& gui);

	void update();
	void draw();

private:

	sf::Texture m_bgTex;
	sf::Sprite m_bg;
	tgui::Gui gui;

	struct Person {

		std::string Name;
		int Age;
		std::string Job;
		std::string Illness;
		int Carbs;
		int Fats;
		int Protein;
		int Fiber;
	};
	
};

#endif // !ADDSTATE_HPP
