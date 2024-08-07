#include "MinGL.h"
#include "Example.h"
#include <iostream>

int main()
{
	// Window sizes
	const int width = 800;
	const int height = 600;
	MinGL minGL;
	if (!minGL.init(width, height, "MinGL"))
		return -1;

	while (!minGL.windowShouldClose())
	{
		minGL.pollEvents();
		minGL.processInput();

		/*** Write Your Code Here ***/ 

		// First Example draws a Cube on the screen

		drawCube(minGL);

		// Second Example demonstrates how to use basic shape drawing functions
		// comment the drawCube(MinGL) and uncomment below line to see the results

		// drawShapes(minGL);

		minGL.flush(0.18f, 0.32f, 0.39f, 1.00f);
	}

	// Clean up
	minGL.shutdown();
	return 0;
}