#include <Light.hpp>
#include <definitions.hpp>
#include <iostream>

int main(int argc, char** argv)
{
	wiringPiSetup();
	LightDiod diod(0);

	while(1)
	{
		char val = std::getchar();
		switch(val)
		{
			case 'q':
			diod.turnOn();
			break;

			case 'w':
			diod.turnOff();
			break;

			default:
			pr_dbg("not supported");
			break;
		}
	}
	return 0;
};