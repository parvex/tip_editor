#pragma once
#include <vector>
#include <memory>
#include "Tips.h"



class TipContainer
{
	std::vector<std::unique_ptr<Tip>> tab;

public:
	void add(const Turn& tip) {} //KURWA{ Turn* ptr = new Turn(tip); tab.push_back(std::move(ptr)); }
	void add(const Forward& tip) {}
	void add(const ExitRamp& tip) {}
	void add(const Destination& tip) {}
	void remove(int n) {}
 	void insert(int n) {}
};
