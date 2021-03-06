#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <memory>
#include <stack>
#include <string>

class State;

namespace sf
{
	class RenderWindow;
}

class StateMachine
{
public:
	StateMachine();

	void run(std::unique_ptr<State> state);

	void nextState();
	void lastState();
	int getStateNum();

	void update();
	void draw();

	bool running() { return m_running; }
	void quit() { m_running = false; }

	template <typename T>
	static std::unique_ptr<T> build(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
	template <typename T>
	static std::unique_ptr<T> build(T* p);

private:
	// The stack of states
	std::stack<std::unique_ptr<State>> m_states;

	bool m_resume;
	bool m_running;
};

template <typename T>
std::unique_ptr<T> StateMachine::build(StateMachine& machine, sf::RenderWindow& window, bool replace)
{
	return std::unique_ptr<T>(new T(machine, window, replace));
}
template <typename T>
std::unique_ptr<T> StateMachine::build(T* p)
{
	return std::unique_ptr<T>(p);
}

#endif // GAMEENGINE_HPP