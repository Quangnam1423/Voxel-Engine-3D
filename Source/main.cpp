#include <iostream>
#include "Engine.h"

int main()
{
	ENGINE->init();
	ENGINE->run();


	delete ENGINE;

	return 0;
}