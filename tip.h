#pragma once

//wskazowki - skret, zawroc, prosto, n-ty zjazd, rondo(prosto, lewo..), 

struct Visitor;

struct Tip
{
	virtual void Accept(Visitor& v) = 0;
};
