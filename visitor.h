#pragma once

#include "Tip.h"

struct Turn;
struct Forward;
struct ExitRamp;
struct Destination;

struct Visitor
{
	virtual void visit_Turn(const Turn& tip) = 0;
	virtual void visit_Forward(const Forward& tip) = 0;
	virtual void visit_ExitRamp(const ExitRamp& tip) = 0;
	virtual void visit_Destination(const Destination &tip) = 0;
};
