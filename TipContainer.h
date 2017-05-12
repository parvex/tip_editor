#pragma once
#include <vector>
#include <memory>
#include "Tips.h"



class TipContainer
{
	std::vector<Tip*> tab;

public:
	void add(Tip* tip) { tab.push_back(tip); }
	void remove(unsigned n) { tab.erase(tab.begin() + n); }
	void insert(unsigned n, Tip* tip) { tab.insert(tab.begin() + n, tip); }
	Tip& operator [] (unsigned n) { return *(tab[n]); }
};

