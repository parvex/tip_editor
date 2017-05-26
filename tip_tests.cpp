#include <stdio.h>
#include <boost/test/auto_unit_test.hpp>
#define BOOST_TEST_MODULE Tips_tests_proj


#include <vector>
#include <memory>
#include <sstream>
#include "Tips.h"
#include "TipContainer.h"
#include "SaveVisitor.h"
#include "ScanLeftTurnVisitor.h"
#include "Interface.h"
#include "PrintVisitor.h"

using namespace std;

BOOST_AUTO_TEST_CASE(Tips_inits)
{
	Turn turn(direction::left);
	Destination dest(direction::right);
	Forward forw(10);
	ExitRamp eramp(10);

	BOOST_CHECK(turn.dir == direction::left);
	BOOST_CHECK(dest.dir == direction::right);
	BOOST_CHECK(forw.n == 10);
	BOOST_CHECK(eramp.n == 10);
}

BOOST_AUTO_TEST_CASE(Tips_gettip)
{
	Turn turn(direction::left);
	Destination dest(direction::right);
	Forward forw(100);
	ExitRamp eramp(10);

	BOOST_CHECK(turn.getTip() == "turn left");
	BOOST_CHECK(dest.getTip() == "your destination will be on your right");
	BOOST_CHECK(forw.getTip() == "move forward 100m");
	BOOST_CHECK(eramp.getTip() == "exit road on 10. ramp");
}

BOOST_AUTO_TEST_CASE(TipContainer_init_and_getting_tip)
{


	TipContainer cont;

	

	cont.add(unique_ptr<Tip>(new Turn(direction::right)));
	cont.add(unique_ptr<Tip>(new Destination(direction::left)));
	cont.add(unique_ptr<Tip>(new Forward(500)));
	cont.add(unique_ptr<Tip>(new ExitRamp(5)));

	BOOST_CHECK(cont[0].getTip() == "turn right");
	BOOST_CHECK(cont[1].getTip() == "your destination will be on your left");
	BOOST_CHECK(cont[2].getTip() == "move forward 500m");
	BOOST_CHECK(cont[3].getTip() == "exit road on 5. ramp");
	BOOST_CHECK(cont.size() == 4);

}


BOOST_AUTO_TEST_CASE(TipContainer_remove)
{


	TipContainer cont;



	cont.add(unique_ptr<Tip>(new Turn(direction::right)));
	cont.add(unique_ptr<Tip>(new Destination(direction::left)));
	cont.add(unique_ptr<Tip>(new Forward(500)));
	cont.add(unique_ptr<Tip>(new ExitRamp(5)));

	cont.remove(2);

	BOOST_CHECK(cont[0].getTip() == "turn right");
	BOOST_CHECK(cont[1].getTip() == "your destination will be on your left");
	BOOST_CHECK(cont[2].getTip() == "exit road on 5. ramp");
	BOOST_CHECK(cont.size() == 3);
}

BOOST_AUTO_TEST_CASE(TipContainer_insert)
{


	TipContainer cont;



	cont.add(unique_ptr<Tip>(new Turn(direction::right)));
	cont.add(unique_ptr<Tip>(new Destination(direction::left)));
	cont.add(unique_ptr<Tip>(new Forward(500)));
	cont.add(unique_ptr<Tip>(new ExitRamp(5)));
	cont.insert(1, unique_ptr<Tip>(new Turn(direction::right)));
	cont.insert(3, unique_ptr<Tip>(new ExitRamp(7)));
	BOOST_CHECK(cont[0].getTip() == "turn right");
	BOOST_CHECK(cont[1].getTip() == "turn right");
	BOOST_CHECK(cont[2].getTip() == "your destination will be on your left");
	BOOST_CHECK(cont[3].getTip() == "exit road on 7. ramp");
	BOOST_CHECK(cont[4].getTip() == "move forward 500m");
	BOOST_CHECK(cont[5].getTip() == "exit road on 5. ramp");
	BOOST_CHECK(cont.size() == 6);

	cont.clear();

	BOOST_CHECK(cont.size() == 0);

}




BOOST_AUTO_TEST_CASE(ScanLeftTurnsVisitor_true)
{
	Turn turn(direction::left);


	ScanLeftTurnsVisitor vis;

	turn.Accept(vis);

	BOOST_CHECK(vis.getFlag() == true);

}

BOOST_AUTO_TEST_CASE(ScanLeftTurnsVisitor_false)
{
	Turn turn(direction::right);


	ScanLeftTurnsVisitor vis;

	turn.Accept(vis);

	BOOST_CHECK(vis.getFlag() == false);

}

BOOST_AUTO_TEST_CASE(Scanlefturnsvisitor_many)
{
	Turn turn(direction::back);
	Destination dest(direction::right);
	Forward forw(100);
	ExitRamp eramp(10);


	ScanLeftTurnsVisitor vis;

	turn.Accept(vis);
	dest.Accept(vis);
	forw.Accept(vis);
	eramp.Accept(vis);

	BOOST_CHECK(vis.getFlag() == false);



}

BOOST_AUTO_TEST_CASE(ScanLeftTurnsVisitor_reset)
{
	Turn turn(direction::left);


	ScanLeftTurnsVisitor vis;

	turn.Accept(vis);

	BOOST_CHECK(vis.getFlag() == true);

	vis.clearFlag();

	BOOST_CHECK(vis.getFlag() == false);

}

BOOST_AUTO_TEST_CASE(TipContainer_visitall_found_left_turn)
{


	TipContainer cont;



	cont.add(unique_ptr<Tip>(new Turn(direction::left)));
	cont.add(unique_ptr<Tip>(new Destination(direction::left)));
	cont.add(unique_ptr<Tip>(new Forward(500)));
	cont.add(unique_ptr<Tip>(new ExitRamp(5)));
	cont.add(unique_ptr<Tip>(new Turn(direction::right)));
	cont.add(unique_ptr<Tip>(new ExitRamp(7)));

	ScanLeftTurnsVisitor vis;


	cont.visitAll(vis);

	BOOST_CHECK(vis.getFlag() == true);

}

BOOST_AUTO_TEST_CASE(TipContainer_visitall_no_left_turn)
{


	TipContainer cont;



	cont.add(unique_ptr<Tip>(new Turn(direction::back)));
	cont.add(unique_ptr<Tip>(new Destination(direction::right)));
	cont.add(unique_ptr<Tip>(new Forward(5200)));
	cont.add(unique_ptr<Tip>(new ExitRamp(5)));
	cont.add(unique_ptr<Tip>(new Turn(direction::right)));
	cont.add(unique_ptr<Tip>(new ExitRamp(7)));

	ScanLeftTurnsVisitor vis;


	cont.visitAll(vis);

	BOOST_CHECK(vis.getFlag() == false);


}

BOOST_AUTO_TEST_CASE(PrintVisitor_print_all)
{


	TipContainer cont;
	stringstream stream;


	cont.add(unique_ptr<Tip>(new Turn(direction::back)));
	cont.add(unique_ptr<Tip>(new Destination(direction::right)));
	cont.add(unique_ptr<Tip>(new Forward(5200)));
	cont.add(unique_ptr<Tip>(new ExitRamp(5)));
	cont.insert(1, unique_ptr<Tip>(new Turn(direction::right)));
	cont.insert(3, unique_ptr<Tip>(new ExitRamp(7)));

	PrintVisitor vis(stream);


	cont.visitAll(vis);


	string test(stream.str());

	string correct = "turn backturn rightyour destination will be on your rightexit road on 7. rampmove forward 5200mexit road on 5. ramp";
	BOOST_CHECK(correct == test);
}



BOOST_AUTO_TEST_CASE(SaveVisitor_saving_and_loading_checking_correctness)
{
	TipContainer cont;
	TipContainer second;

	cont.add(unique_ptr<Tip>(new Turn(direction::back)));
	cont.add(unique_ptr<Tip>(new Destination(direction::right)));
	cont.add(unique_ptr<Tip>(new Forward(5200)));
	cont.add(unique_ptr<Tip>(new ExitRamp(5)));
	cont.add(unique_ptr<Tip>(new Turn(direction::right)));
	cont.add(unique_ptr<Tip>(new ExitRamp(7)));

	string fileName = "test";

	SaveVisitor vis(fileName.c_str());

	cont.visitAll(vis);

	vis.close();

	loadTips(second, fileName.c_str());

	BOOST_REQUIRE(cont.size() == second.size());

	for (unsigned i = 0; i < cont.size(); i++)
	{
		BOOST_CHECK(cont[i].getTip() == second[i].getTip());

	}


}



BOOST_AUTO_TEST_CASE(SaveVisitor_saving_and_loading_checking_correctness_more)
{
	TipContainer cont;
	TipContainer second;

	cont.add(unique_ptr<Tip>(new Turn(direction::back)));
	cont.add(unique_ptr<Tip>(new Destination(direction::left)));
	cont.add(unique_ptr<Tip>(new Forward(5200)));
	cont.add(unique_ptr<Tip>(new ExitRamp(5)));
	cont.add(unique_ptr<Tip>(new Turn(direction::right)));
	cont.add(unique_ptr<Tip>(new ExitRamp(7)));
	cont.add(unique_ptr<Tip>(new Turn(direction::left)));
	cont.add(unique_ptr<Tip>(new Destination(direction::left)));
	cont.add(unique_ptr<Tip>(new Forward(3400)));
	cont.add(unique_ptr<Tip>(new ExitRamp(6)));

	string fileName = "test";

	SaveVisitor vis(fileName.c_str());

	cont.visitAll(vis);
	vis.close();
	loadTips(second, fileName.c_str());
	BOOST_REQUIRE(cont.size() == second.size());
	for (unsigned i = 0; i < cont.size(); i++)
	{
		BOOST_CHECK(cont[i].getTip() == second[i].getTip());

	}
}






//// seven ways to detect and report the same error:
//BOOST_CHECK(add(2, 2) == 4);           // #1 continues on error

//BOOST_REQUIRE(add(2, 2) == 4);         // #2 throws on error

//if (add(2, 2) != 4)
//	BOOST_ERROR("Ouch...");             // #3 continues on error

//if (add(2, 2) != 4)
//	BOOST_FAIL("Ouch...");              // #4 throws on error

//if (add(2, 2) != 4) throw "Ouch...";    // #5 throws on error

//BOOST_CHECK_MESSAGE(add(2, 2) == 4,     // #6 continues on error
//	"add(..) result: " << add(2, 2));

//BOOST_CHECK_EQUAL(add(2, 2), 4);       // #7 continues on error