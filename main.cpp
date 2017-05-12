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
	test.n = 25;

	cout << test.n << endl;

	test.Accept(vis);


	cout << test.n << endl;

	Turn lewo(direction::left);


	TipContainer cont;
	
	cont.add(&lewo);

	cont[0].showTip();



	system("pause");

	return 0;
}