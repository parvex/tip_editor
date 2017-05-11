#pragma once
#include "Visitor.h"

enum direction { left, right, forward, back };

struct Turn : Tip //zakret
{

	direction dir;

	virtual void Accept(Visitor& v)
	{
		v.visit_Turn(*this);
	}
};


struct Forward : Tip //jazda prosto
{
	int m; //metres

	virtual void Accept(Visitor& v)
	{
		v.visit_Forward(*this);
	}
};

struct ExitRamp : Tip //n-ty zjazd
{
	int n;

	virtual void Accept(Visitor& v)
	{
		v.visit_ExitRamp(*this);
	}
};



struct Destination : Tip //po ktorej stronie jest cel
{
	direction dir;

	virtual void Accept(Visitor& v)
	{
		v.visit_Destination(*this);
	}
};
