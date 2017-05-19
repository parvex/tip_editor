#include "Interface.h"
#include <cstdlib>
#include <thread>
#include <chrono>
#include <string>
#include "SaveVisitor.h"
#include "ScanLeftTurnVisitor.h"
#include "PrintVisitor.h"
using namespace std;

void clear_screen()
{
#ifdef _WIN32
	 system("cls");
#else
	// Assume POSIX
	 system("clear");
#endif
}

void press_enter()
{
	cout << "press enter to continue\n";
	cin.ignore(); 
	cin.get();
}

int Interface::exec() //start menu
{	

	char choice;
	while (true)
	{
		clear_screen();
		 cout << "Welcome in arrival tip editor, what do you want to do?\n"
		<< "1. Create new set of tips\n"
		<< "2. Load existing set from file\n"
		<< "q. Exit application\n\n";
		 cin.clear();
		 cin.sync();
		 cin >> choice;
		if (! cin) continue;
		switch (choice)
		{
		case '1': {addMenu(); if(cont.size() != 0) mainMenu(); break; }
		case '2': {load(); if (cont.size() != 0) mainMenu(); break; }
		case 'q': {return 0; break; }
		default: { cout << "wrong input"; press_enter(); break; }
		}

	}


}

void Interface::addMenu(size_t index)
{
	index = index ? index : cont.size(); // if index is == 0 i add at the end of vector
	char choice;
	while (true)
	{
		clear_screen();
		cout << "Adding at: " << index  << ". index" << "                              number of tips : " << cont.size() << endl << endl
		<< "Choose kind of tip:\n"
		<< "1. Move forward\n"
		<< "2. Turn\n"
		<< "3. Exit ramp\n"
		<< "4. Destination side\n"
		<< "q. quit\n\n";

		 cin.clear();
		 cin.sync();
		 cin >> choice;
		if (! cin) continue;
		switch (choice)
		{
		case '1': {addForward(index); return; break; }
		case '2': {addTurn(index); return; break; }
		case '3': {addExitRamp(index); return; break; }
		case '4': {addDestination(index); return; break; }
		case 'q': {return; break; }
		default: {cout << "wrong input"; press_enter(); break; }
		}

	}


}

void Interface::addForward(size_t index)
{
	size_t n;
	while (true)
	{
		clear_screen();
		cout << "How many metres would you like to drive forward?\n\n";


		cin.clear();
		cin.sync();
		cin.get();  //moze nie dzialac na linuxie - "zjada" enter
		cin >> n;
		if (!cin) { cout << "wrong input"; press_enter(); continue; }
		else
		{
			if (index == cont.size())
				cont.add(new Forward(n));
			else
				cont.insert(index, new Forward(n));
			return;
		}

	}
}

void Interface::addTurn(size_t index)
{
	char choice;
	direction dir;
	bool choosen = 0;
	while (!choosen)
	{
		clear_screen();
		cout << "Choose direction to turn:\n"
		<< "r. right\n"
		<< "l. left\n"
		<< "b. turn back\n\n";

		cin.clear();
		cin.sync();
		cin >> choice;
		if (!cin) { cout << "wrong input"; press_enter(); continue; }

		switch (choice)
		{
		case 'r': {dir = direction::right; choosen = 1; break; }
		case 'l': {dir = direction::left; choosen = 1; break; }
		case 'b': { dir = direction::back; choosen = 1; break; }
		default : { cout << "wrong input"; press_enter();  }
		}

	}
	if (index == cont.size())
		cont.add(new Turn(dir));
	else
		cont.insert(index, new Turn(dir));
	return;
}

void Interface::addExitRamp(size_t index)
{
	size_t n;
	while (true)
	{
		clear_screen();
		cout << "On which ramp would you like to exit?\n\n";

		cin.clear();
		cin.sync();
		cin >> n;
		if (!cin) { cout << "wrong input"; press_enter(); continue; }
		else
		{
			if (index == cont.size())
				cont.add(new ExitRamp(n));
			else
				cont.insert(index, new ExitRamp(n));
			return;
		}

	}
}

void Interface::addDestination(size_t index)
{
	char choice;
	direction dir;
	bool choosen = 0;
	while (!choosen)
	{
		clear_screen();
		cout << "Choose direction to turn:\n"
			<< "r. right\n"
			<< "l. left\n\n";

		cin.clear();
		cin.sync();
		cin >> choice;
		if (!cin) { cout << "wrong input"; press_enter(); continue; }

		switch (choice)
		{
		case 'r': {dir = direction::right; choosen = 1; break; }
		case 'l': {dir = direction::left; choosen = 1; break; }
		default: { cout << "wrong input"; press_enter(); break; }

		}

	}
	if (index == cont.size())
		cont.add(new Destination(dir));
	else
		cont.insert(index, new Destination(dir));
	return;
}

void Interface::input()
{
	size_t index;

	while (1)
	{
		clear_screen();
		show();
		cout << "Choose index to input tip:\n\n";
		cin.clear();
		cin.sync();
		cin >> index;
		if (!cin || index > cont.size()) { cout << "wrong input\n"; press_enter(); continue; }
		else
			break;
	}
	addMenu(index);
	return;
}

void Interface::scanLeftTurns()
{
	ScanLeftTurnsVisitor visitor;
	cont.visitAll(visitor);
	if (visitor.lTurnFlag == true)
		cout << "Left turns were found!!!\n\n";
	else
		cout << "No left turns were found ;)\n";
	press_enter();
}

void Interface::remove()
{
	size_t index;

	while (1)
	{
		clear_screen();
		show();
		cout << "Choose index to remove:\n\n";
		cin.clear();
		cin.sync();
		cin >> index;
		if (!cin || index >= cont.size()) { cout << "wrong input\n"; press_enter(); continue; }
		else 
			break;
	}
	cont.remove(index);
	return;
}

size_t Interface::index()
{
	size_t index;
	cout << "Choose index for your purpose:\n\n";
	while (1)
	{
		cin.clear();
		cin.sync();
		cin >> index;
		if (!cin) { cout << "wrong input\n"; press_enter(); continue; }
		return index;
	}
}

void Interface::show()
{
	PrintVisitor vis(std::cout);
	clear_screen();
	cout << "Your set of tips:\n";
	for (size_t i = 0; i < cont.size(); i++)
	{
		cout << i << ". ";
		cont[i].Accept(vis);
	}
}

void Interface::save()
{
	string fileName;

	clear_screen();
	cout << "Enter file name:\n\n";
	cin >> fileName;

	SaveVisitor vis(fileName.c_str());

	cont.visitAll(vis);

}

void Interface::load()
{
	while (true)
	{
		string fileName;

		clear_screen();
		cout << "Enter file name:\n\n";
		cin >> fileName;


		if (!loadTips(cont, fileName.c_str())) return;

		cout << "error while reading(file may not exist or it's type is wrong)\n";
		press_enter();

	}
	///////tu


}

void Interface::mainMenu()
{
	char choice;
	while (true)
	{
		clear_screen();
		cout << "MAIN MENU\n"
			<< "choose option\n"
			<< "a. Add new tip\n"
			<< "r. Remove tip\n"
			<< "i. Insert tip on choosen index\n"
			<< "s. Show all tips\n"
			<< "l. Seek left turns\n\n"



			<< "w. Write set to file\n"
			<< "q. Close set\n\n";
		cin.clear();
		cin.sync();
		cin >> choice;
		if (!cin) continue;
		switch (choice)
		{
		case 'a': {addMenu(); break; }
		case 'r': {remove(); break; }
		case 'i': {input(); break; }
		case 's': {show(); press_enter(); break; }
		case 'l': { scanLeftTurns(); break; }
		case 'w': { save(); break; }
		case 'q': { cont.clear(); return; break; }
		default: { cout << "wrong input\n"; press_enter(); break; }
		}

	}
}
