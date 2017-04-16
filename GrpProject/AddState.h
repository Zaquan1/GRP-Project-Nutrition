#ifndef ADDSTATE_HPP
#define ADDSTATE_HPP

#include "State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <TGUI\TGUI.hpp>
#include <iostream>
#include <fstream>


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

	void submit(tgui::EditBox::Ptr First, tgui::EditBox::Ptr Age, tgui::EditBox::Ptr Gender, tgui::EditBox::Ptr Illness,
		tgui::EditBox::Ptr Job, tgui::EditBox::Ptr Carbs, tgui::EditBox::Ptr Fats, tgui::EditBox::Ptr Protein,
		tgui::EditBox::Ptr Fiber);
	void loadWidgets(tgui::Gui& gui);

	void update();
	void draw();

	void isNumber(std::vector <std::string> &num);
	void isWord(std::vector <std::string> &word);

	void setErrorTextStyle();

	void isValid();
	void errorPrint();

private:

	sf::Texture m_bgTex;
	sf::Sprite m_bg;
	sf::Font font;
	sf::Text error[9];
	sf::FloatRect errTextRect;
	tgui::Gui gui;

	std::vector<std::string> v_words;
	std::vector<std::string> v_nums;

	bool word_flag[4];
	bool num_flag[5];

	bool all_words_valid;
	bool all_num_valid;

};

#endif // !ADDSTATE_HPP
