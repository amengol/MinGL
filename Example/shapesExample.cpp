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

		// declare color variable
		const MinGLColor green{ 0.0f, 1.0f, 0.0f, 1.0f };

        // draw a circle
		// takes the center of circle and radius as parameters
		// if (x, y) is then center of circle and rad is the radius->
		// drawCircle(x, y, rad, color)
        minGL.drawCircle(400, 300, 100, green);

        // draw a rectangle
		// takes two endpoints of a diagonal of rectangle and color as parameters
		// if(x1,y1) and (x2,y2) are endpoints of one of the diagonals->
		// drawRectangle(x1, y1, x2, y2, color)
        minGL.drawRectangle(300, 200, 500, 400, green);

        // draw lines
		// takes the endpoints of line as parameters
		// if (x1, y1) and (x2, y2) are the endpoints of the line->
		// drawline(x1, y1, x2, y2, color)
        minGL.drawLine(400, 150, 400, 450, green);
        minGL.drawLine(250, 300, 550, 300, green); 

		minGL.flush(0.18f, 0.32f, 0.39f, 1.00f);
	}

	// Clean up
	minGL.shutdown();
	return 0;
}