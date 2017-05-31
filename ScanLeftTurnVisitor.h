#pragma once
#include "Tips.h"



struct ScanLeftTurnsVisitor : public Visitor
{
private:
	bool lTurnFlag;
	size_t amount;
public:
	void clearAmount() { amount = 0; }
	size_t getAmount() { return amount; }
	ScanLeftTurnsVisitor() : lTurnFlag(false), amount(0) {}
	virtual void visit_Turn(const Turn& tip) { if (tip.dir == direction::left) { lTurnFlag = true; ++amount; } }
	virtual void visit_Forward(const Forward& tip) {}
	virtual void visit_ExitRamp(const ExitRamp& tip) {}
	virtual void visit_Destination(const Destination &tip) {}
	bool getFlag() { return lTurnFlag; }
	void clearFlag() { lTurnFlag = false; }
};