#include <iostream>
using namespace std;

#include "Tips.h"
#include "SaveVisitor.h"
#include "ScanLeftTurnVisitor.h"
#include "Interface.h"






int main()
{

	Forward test;
	SaveVisitor vis;
	test.m = 25;

	cout << test.m << endl;

	test.Accept(vis);


	cout << test.m << endl;


	system("pause");

	return 0;
}