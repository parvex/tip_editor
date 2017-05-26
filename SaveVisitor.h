#pragma once
#include "Tips.h"
#include <iostream>
#include <fstream>

struct SaveVisitor : public Visitor
{

public:
	std::string fileName;
private:
	std::ofstream out;
public:
	SaveVisitor(const char* name) : fileName(name), out(name, std::ios::out | std::ios::binary) {}
	~SaveVisitor() { out.close(); }
	void close() { out.close(); }
	void open() { out.open(fileName.c_str(), std::ios::out | std::ios::binary); }
	virtual void visit_Turn(const Turn& tip) { out << 'T'; out.write(reinterpret_cast<const char*>(&tip.dir), sizeof(direction)); }
	virtual void visit_Forward(const Forward& tip) { out << 'F';  out.write(reinterpret_cast<const char*>(& tip.n), sizeof(size_t)); }
	virtual void visit_ExitRamp(const ExitRamp& tip) { out << 'E'; out.write(reinterpret_cast<const char*>(& tip.n), sizeof(size_t)); }
	virtual void visit_Destination(const Destination &tip) { out << 'D'; out.write(reinterpret_cast<const char*>(& tip.dir), sizeof(direction)); }
};

