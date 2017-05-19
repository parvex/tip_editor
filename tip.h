#pragma once
#include <string>

//wskazowki - skret, zawroc, prosto, n-ty zjazd, rondo(prosto, lewo..), 

struct Visitor;

struct Tip
{
	virtual ~Tip() {}
	virtual void Accept(Visitor& v) = 0;
	virtual std::string getTip() const = 0;
};
