#include <iostream>
using namespace std;

#include <vector>
#include "Tips.h"
#include "SaveVisitor.h"
#include "ScanLeftTurnVisitor.h"
#include "Interface.h"



int main()
{
	TipContainer container;
	Interface programme(container);
	return programme.exec();
}