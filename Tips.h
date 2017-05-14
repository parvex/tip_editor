#pragma once
#include "Visitor.h"
#include <iostream>

enum direction { left, right, back };

struct Turn : Tip //zakret
{
	Turn(direction dir = direction::right) : dir(dir) {};
	direction dir;

	virtual void showTip() {
		std::cout << "turn ";
		if (dir == direction::left) std::cout << "left";
		else if (dir == direction::right) std::cout << "right";
		else std::cout << "back";
		std::cout << std::endl;	
	}

	virtual void Accept(Visitor& v)
	{
		v.visit_Turn(*this);
	}
};


struct Forward : Tip //jazda prosto
{
	size_t n; //metres

	Forward(size_t n = 500) : n(n) {}


	virtual void showTip()
	{
		std::cout << "move forward ";
		if (n >= 1000) std::cout << n / 1000. << "km\n";
		else std::cout << n << "m\n";

	}


	virtual void Accept(Visitor& v)
	{
		v.visit_Forward(*this);
	}
};

struct ExitRamp : Tip //n-ty zjazd
{
	size_t n;

	ExitRamp(size_t n) : n(n) {}

	virtual void showTip()
	{
		std::cout << "exit road on " << n << ". ramp" << std::endl;
	}

	virtual void Accept(Visitor& v)
	{
		v.visit_ExitRamp(*this);
	}
};



struct Destination : Tip //po ktorej stronie jest cel
{
	direction dir;

	Destination(direction dir = direction::right) : dir(dir) {}

	virtual void showTip() {
		std::cout << "your destination will be on your";
		if (dir == direction::left) std::cout << "left";
		else if (dir == direction::right) std::cout << "right";
		else std::cout << "error";
		std::cout << "side" << std::endl;
	}

	virtual void Accept(Visitor& v)
	{
		v.visit_Destination(*this);
	}
};
