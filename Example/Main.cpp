#include "MinGL.h"
#include <iostream>

// Based on https://github.com/ssloy/tinyrenderer/wiki, Lesson 1
void drawLine(int x0, int y0, int x1, int y1, const MinGLColor& color, const MinGL& minGL)
{
	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror = std::abs(dy) * 2;
	int error = 0;
	int y = y0;
	for (int x = x0; x < x1; ++x) {
		if (steep) {
			minGL.putPixel(y, x, color);
		}
		else {
			minGL.putPixel(x, y, color);
		}
		error += derror;
		if (error > dx) {
			y += (y1 > y0 ? 1 : -1);
			error -= dx * 2;
		}
	}
}

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

		// Draw a green cube
		const MinGLColor green{ 0.0f, 1.0f, 0.0f, 1.0f };
		int c0X = 300;
		int c0Y = 250;
		int c1X = c0X;
		int c1Y = c0Y + 100;
		drawLine(c0X, c0Y, c1X, c1Y, green, minGL);
		int c2X = c0X + 100;
		int c2Y = c0Y + 100;
		drawLine(c1X, c1Y, c2X, c2Y, green, minGL);
		int c3X = c0X + 100;
		int c3Y = c0Y;
		drawLine(c2X, c2Y, c3X, c3Y, green, minGL);
		drawLine(c3X, c3Y, c0X, c0Y, green, minGL);
		int c4X = c1X + 50;
		int c4Y = c1Y + 50;
		drawLine(c1X, c1Y, c4X, c4Y, green, minGL);
		int c5X = c4X + 100;
		int c5Y = c4Y;
		drawLine(c4X, c4Y, c5X, c5Y, green, minGL);
		drawLine(c2X, c2Y, c5X, c5Y, green, minGL);
		int c6X = c3X + 50;
		int c6Y = c3Y + 50;
		drawLine(c3X, c3Y, c6X, c6Y, green, minGL);
		drawLine(c5X, c5Y, c6X, c6Y, green, minGL);

		minGL.flush(0.18f, 0.32f, 0.39f, 1.00f);
	}

	// Clean up
	minGL.shutdown();
	return 0;
}