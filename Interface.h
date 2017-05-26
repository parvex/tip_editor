#pragma once
#include "Tip.h"
#include "TipContainer.h"
#include <iostream>
class Interface
{
public:
	Interface(TipContainer& container, std::istream& in = std::cin) : cont(container), inputs(in) {} //	Interface(TipContainer& container, std::istream& in = std::cin, std::ostream& out = std::cout) : cont(container), inputs(in), outputs(out) {}
	int exec();
private:
	bool exit = false;
	TipContainer& cont;
	std::istream& inputs;
	void addMenu(size_t index = 0);
	void addForward(size_t index);
	void addTurn(size_t index);
	void addExitRamp(size_t index);
	void addDestination(size_t index);
	void input();
	void scanLeftTurns();
	void remove();
	void show();
	void save();
	void load();
	void mainMenu();

	void press_enter();
	char getOneChar();
	int putOneNatural(size_t& c);
};
