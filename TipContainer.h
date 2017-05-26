#pragma once
#include <vector>
#include <memory>
#include "Tips.h"
#include <fstream>


class TipContainer
{
	std::vector<std::unique_ptr<Tip>> tab;

public:
	void add(std::unique_ptr<Tip> tip) { tab.push_back(std::move(tip)); }
	void remove(size_t n) {  tab.erase(tab.begin() + n); }
	void insert(size_t n, std::unique_ptr<Tip> tip) { tab.insert(tab.begin() + n, std::move(tip)); }
	Tip& operator [] (size_t n) { return *(tab[n]); }
	void visitAll(Visitor& vis) { for (size_t i = 0; i < tab.size(); i++) { tab[i]->Accept(vis); } }
	size_t size() { return tab.size(); }
	void clear() { tab.clear(); }
};

int loadTips(TipContainer& cont, const char* fileName);
