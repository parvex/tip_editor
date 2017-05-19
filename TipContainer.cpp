#include "TipContainer.h"

int loadTips(TipContainer& cont, const char* fileName)
{
	std::ifstream reader(fileName);
	if (!reader) return -1; //error while opening file

	char type;
	int dir;
	size_t n;


	while (!reader.eof())
	{
		reader >> type;
		if (type == 'T')
		{
			reader >> dir;
			//	reader dir;
			cont.add(new Turn(static_cast<direction>(dir)));
		}
		else if (type == 'D')
		{
			reader >> dir;
			//	reader dir;
			cont.add(new Destination(static_cast<direction>(dir)));
		}
		else if (type == 'F')
		{
			reader >> n;
			cont.add(new Forward(n));
		}
		else if (type == 'E')
		{
			reader >> n;
			cont.add(new ExitRamp(n));
		}
		else return 1; // error while reading
	}
	return 0;
}