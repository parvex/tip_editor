#include "TipContainer.h"





int loadTips(TipContainer& cont, const char* fileName)
{
	std::ifstream reader(fileName);
	if (!reader) return -1; //error while opening file

	char type;
	direction dir;
	size_t n;


	while (reader >> type)
	{


		if (type == 'T')
		{
			reader.read(reinterpret_cast<char*>(&dir), sizeof(direction));
			cont.add(std::unique_ptr<Tip>(new Turn(dir)));
		}
		else if (type == 'D')
		{
			reader.read(reinterpret_cast<char*>(&dir), sizeof(direction));
			cont.add(std::unique_ptr<Tip>(new Destination(dir)));
		}
		else if (type == 'F')
		{
			reader.read(reinterpret_cast<char*>(&n), sizeof(size_t));
			cont.add(std::unique_ptr<Tip>(new Forward(n)));
		}
		else if (type == 'E')
		{
			reader.read(reinterpret_cast<char*>(&n), sizeof(size_t));
			cont.add(std::unique_ptr<Tip>(new ExitRamp(n)));
		}
		else return 1; // error while reading
	}
	return 0;
}



















//
//int loadTips(TipContainer& cont, const char* fileName)
//{
//	std::ifstream reader(fileName);
//	if (!reader) return -1; //error while opening file
//
//	char type;
//	int dir;
//	size_t n;
//
//
//	while (!reader.eof())
//	{
//		reader >> type;
//		if (type == 'T')
//		{
//			reader >> dir;
//			//	reader dir;
//			cont.add(std::unique_ptr<Tip>(new Turn(static_cast<direction>(dir))));
//		}
//		else if (type == 'D')
//		{
//			reader >> dir;
//			//	reader dir;
//			cont.add(std::unique_ptr<Tip>(new Destination(static_cast<direction>(dir))));
//		}
//		else if (type == 'F')
//		{
//			reader >> n;
//			cont.add(std::unique_ptr<Tip>(new Forward(n)));
//		}
//		else if (type == 'E')
//		{
//			reader >> n;
//			cont.add(std::unique_ptr<Tip>(new ExitRamp(n)));
//		}
//		else return 1; // error while reading
//	}
//	return 0;
//}