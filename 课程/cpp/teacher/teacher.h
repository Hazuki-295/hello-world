#include <iostream>
#include <string>
using namespace std;

struct Teacher
{
	string position, house;

public :
	Teacher() :position(), house() {}
	Teacher(const char pos[], const char housetype[])
	{
		position = pos;
		house = housetype;
	}

	void print()
	{
		cout << "position:" << position << "\nhouse:" << house << "\n\n";
	}
} teacher[4];

int test()
{
	teacher[0] = Teacher("Professor", "House");
	teacher[1] = Teacher("Associate professor", "Apartment");
	teacher[2] = Teacher("Lecturer", "Studio");
	teacher[3] = Teacher("Assistant", "Single");
	
	for (int i = 0; i < 4; i++)
	{
		teacher[i].print();
	}

	return 0;
}