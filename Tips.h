#pragma once
#include "Visitor.h"
#include <iostream>

enum direction { left, right, back };

struct Turn : Tip //zakret
{
	Turn(direction dir = direction::right) : dir(dir) {};
	direction dir;

	virtual std::string getTip() const{

		if (dir == direction::left) return "turn left\n";
		else if (dir == direction::right) return "turn right\n";
		else return "turn back\n";	
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



	virtual std::string getTip() const
	{
		if (n >= 1000)   return "move forward " + std::to_string(n / 1000.) + "km\n";
		else return "move forward " + std::to_string(n) + "m\n";
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

	virtual std::string getTip() const
	{
		return  "exit road on " + std::to_string(n) + ". ramp\n";
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



	virtual std::string getTip() const
	{
		if (dir == direction::left) return "your destination will be on your left\n";
		else if (dir == direction::right) return "your destination will be on your right\n";
		else return "destination error\n";
	}

	virtual void Accept(Visitor& v)
	{
		v.visit_Destination(*this);
	}
};
