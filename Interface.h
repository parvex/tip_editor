#pragma once
#include "Tip.h"
#include "TipContainer.h"

class Interface
{
private:
	TipContainer& cont;

public:
	Interface(TipContainer& cont) : cont(cont) {}
	int exec();
	void addMenu(size_t index = 0 );
	void addForward(size_t index);
	void addTurn(size_t index);
	void addExitRamp(size_t index);
	void addDestination(size_t index);
	void input();
	void scanLeftTurns();
	void remove();
	size_t index();
	void show();
	void save();
	void load();
	void mainMenu();
};
