#pragma once
#include "Visitor.h"
#include <iostream>

enum direction { left, right, forward, back };

struct Turn : Tip //zakret
{
	Turn(direction dir = direction::right) : dir(dir) {};
	direction dir;

	virtual void showTip() {
		std::cout << "turn ";
		if (dir == direction::left) std::cout << "left";
		else if (dir == direction::right) std::cout << "right";
		else std::cout << "error";
		std::cout << std::endl;	
	}

	virtual void Accept(Visitor& v)
	{
		v.visit_Turn(*this);
	}
};


struct Forward : Tip //jazda prosto
{
	unsigned n; //metres

	virtual void showTip()
	{
		std::cout << "drive forward " << n << "metres" << std::endl;

	}


	virtual void Accept(Visitor& v)
	{
		v.visit_Forward(*this);
	}
};

struct ExitRamp : Tip //n-ty zjazd
{
	unsigned n;

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
