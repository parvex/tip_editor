#include <stdio.h>
#include <boost/test/auto_unit_test.hpp>
#define BOOST_TEST_MODULE Tips_tests_proj


#include <vector>
#include <memory>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "Tips.h"
#include "TipContainer.h"
#include "SaveVisitor.h"
#include "ScanLeftTurnVisitor.h"
#include "Interface.h"
#include "PrintVisitor.h"

using namespace std;



BOOST_AUTO_TEST_SUITE(Testing_interface_inputs)

BOOST_AUTO_TEST_CASE(Interface_adding_forward)
{


	TipContainer cont;
	std::stringstream in;
	Interface prog(cont, in);

	in << "1\n1\n1500\ne\n";
	prog.exec();


	BOOST_CHECK(cont[0].getTip() == "move forward 1500m" && cont.size() == 1);
}

BOOST_AUTO_TEST_CASE(Interface_adding_turn)
{

	TipContainer cont;
	std::stringstream in;
	Interface prog(cont, in);

	in << "1\n2\nl\ne\n";
	prog.exec();


	BOOST_CHECK(cont[0].getTip() == "turn left" && cont.size() == 1);
}

BOOST_AUTO_TEST_CASE(Interface_adding_exit_ramp)
{

	TipContainer cont;
	std::stringstream in;
	Interface prog(cont, in);


	in << "1\n3\n1500\ne\n";
	prog.exec();


	BOOST_CHECK(cont[0].getTip() == "exit road on 1500. ramp" && cont.size() == 1);
}

BOOST_AUTO_TEST_CASE(Interface_adding_destination)
{

	TipContainer cont;
	std::stringstream in;
	Interface prog(cont, in);


	in << "1\n4\nr\ne\n";
	prog.exec();


	BOOST_CHECK(cont[0].getTip() == "your destination will be on your right" && cont.size() == 1);
}

char getRandomchar()
{
	srand(time(NULL));
	return ((std::rand() % 127) + 0);
}

string getRandomStringWithout(const char* tab)
{
	srand(time(NULL));

	string random;
	bool cancel = false;
	int length = ((std::rand() % 300) + 1);
	char c;
	for (int i = 0; i < length; i++)
	{
		cancel = false;

		c = ((std::rand() % 127) + 0);

		for (int j = 0; tab[j] != 0; j++)
		{
			if (tab[j] == c) cancel = true;
		}
		if (cancel) continue;
		else
			random += c;
	}

	return random;

}




BOOST_AUTO_TEST_CASE(Interface_testing_remove_input_single_chars)
{

	TipContainer cont;
	std::stringstream in;
	Interface prog(cont, in);

	in << "1\n2\nl\nr\n";
	for (int i = 0; i < 10; i++)
	{
		in << getRandomStringWithout("10\n") << "\n\n";
	}

	in << "0\ne\n";

	prog.exec();






	BOOST_CHECK(cont[0].getTip() == "turn left" && cont.size() == 1);
}


BOOST_AUTO_TEST_CASE(Interface_testing_first_input)
{

	TipContainer cont;
	std::stringstream in;
	Interface prog(cont, in);

	for (int i = 0; i < 10; i++)
	{
		in << getRandomStringWithout("12q\n") << "\n\n";
	}

	in << "q\n";

	prog.exec();


	BOOST_CHECK(cont.size() == 0);
}


BOOST_AUTO_TEST_CASE(Interface_testing_add_menu_input)
{

	TipContainer cont;
	std::stringstream in;
	Interface prog(cont, in);

	in << "1\n1\n1200\n";
	for (int i = 0; i < 10; i++)
	{
		in << getRandomStringWithout("arislweq\n") << "\n\n";
	}

	in << "e\n";

	prog.exec();


	BOOST_CHECK(cont.size() == 1 && cont[0].getTip() == "move forward 1200m");
}


BOOST_AUTO_TEST_CASE(Interface_testing_load_menu_input)
{

	TipContainer cont;
	std::stringstream in;
	Interface prog(cont, in);

	in << "1\n1\n1500\na\n2\nl\na\n1\n1500\ni\n";
	for (int i = 0; i < 5; i++)
	{
		in << getRandomStringWithout("012\n") << "\n\n";
	}

	in << "0\ne\n";

	prog.exec();


	BOOST_CHECK(cont.size() == 3);
}

BOOST_AUTO_TEST_SUITE_END()
