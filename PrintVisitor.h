#pragma once
#include "Tips.h"
#include <iostream>


struct PrintVisitor : public Visitor
{
	PrintVisitor(std::ostream& out) : out(out) {}

private:
	std::ostream& out;
public:
	virtual void visit_Turn(const Turn& tip) { out << tip.getTip(); }
	virtual void visit_Forward(const Forward& tip) { out << tip.getTip(); }
	virtual void visit_ExitRamp(const ExitRamp& tip) { out << tip.getTip(); }
	virtual void visit_Destination(const Destination &tip) { out << tip.getTip(); }
};
