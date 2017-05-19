#pragma once
#include <vector>
#include <memory>
#include "Tips.h"
#include <fstream>


class TipContainer
{
	std::vector<Tip*> tab;

public:
	~TipContainer() {
		for (size_t i = 0; i < tab.size(); i++)
			delete tab[i]; }
	void add(Tip* tip) { tab.push_back(tip); }
	void remove(size_t n) { delete tab[n];  tab.erase(tab.begin() + n); }
	void insert(size_t n, Tip* tip) { tab.insert(tab.begin() + n, tip); }
	Tip& operator [] (size_t n) { return *(tab[n]); }
	void visitAll(Visitor& vis) { for (Tip*& tip : tab) { tip->Accept(vis); } }
	size_t size() { return tab.size(); }
	void clear() { 
		for (size_t i = 0; i < tab.size(); i++)
			delete tab[i];
		tab.clear();
	}
};

int loadTips(TipContainer& cont, const char* fileName);
