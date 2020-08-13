#include <iostream>
#include <definitions.hpp>
#include "L298N.hpp"

int main(int argc, char** argv)
{
	wiringPiSetup();
	L298N l298n(0, 1, 2, 3, 4, 5);
	float fraction = std::stof(argv[1]);
	while(1)
	{
		char val = std::getchar();
		switch(val)
		{
			
			case 'w':
			l298n.activateA(L298N::Direction::Clockwise, fraction);
			pr_dbg("activateA");
			break;

			case 'q':
			l298n.activateB(L298N::Direction::Clockwise, fraction);
			pr_dbg("activateB");
			break;

			case 'a':
			l298n.stopA();
			pr_dbg("stopA");
			break;

			case 's':
			l298n.stopB();
			pr_dbg("stopB");
			break;

			default:
			break;
		}
	}
}