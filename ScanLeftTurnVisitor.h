#pragma once
#include "Tips.h"



struct ScanLeftTurnsVisitor : public Visitor
{
	ScanLeftTurnsVisitor() : lTurnFlag(false) {}

	bool lTurnFlag;
	virtual void visit_Turn(const Turn& tip) {if (tip.dir == direction::left) lTurnFlag = true;}
	virtual void visit_Forward(const Forward& tip) {}
	virtual void visit_ExitRamp(const ExitRamp& tip) {}
	virtual void visit_Destination(const Destination &tip) {}
};