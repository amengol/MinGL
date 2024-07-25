#include "MinGL.h"
#include <iostream>

int main()
{
	// Window sizes
	const int width = 800;
	const int height = 600;
	MinGL minGL;
	if (!minGL.init(width, height, "MinGL"))
		return -1;

	const char* glsl_version = "#version 130";

	while (!minGL.windowShouldClose())
	{
		minGL.pollEvents();
		minGL.processInput();

		const MinGLColor green{ 0.0f, 1.0f, 0.0f, 1.0f };

        // draw a circle
        minGL.drawCircle(400, 300, 100, green);

        //draw a rectangle
        minGL.drawRectangle(300, 200, 500, 400, green);

        // draw lines
        minGL.drawLine(400, 150, 400, 450, green);
        minGL.drawLine(250, 300, 550, 300, green); 

		minGL.flush(0.18f, 0.32f, 0.39f, 1.00f);
	}

	// Clean up
	minGL.shutdown();
	return 0;
}