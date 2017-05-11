#pragma once
#include "Tips.h"


struct SaveVisitor : public Visitor
{

	virtual void visit_Turn(const Turn& tip);
	virtual void visit_Forward(const Forward& tip);
	virtual void visit_ExitRamp(const ExitRamp& tip);
	virtual void visit_Destination(const Destination &tip);

};
