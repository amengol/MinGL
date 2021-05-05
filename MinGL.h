#pragma once

#include <cstdint>

struct GLFWwindow;

struct MinGLColor
{
	std::uint8_t rgba[4] = { 0,0,0,0 };
};

class MinGL
{
public:
	bool init(unsigned width, unsigned height, const char* title);
	bool windowShouldClose() const;
	void pollEvents() const;
	void processInput() const;
	void putPixel(int x, int y, const MinGLColor& color) const;
	void flush(float r, float g, float b, float a);
	void shutdown() const;
	GLFWwindow* getWindow();

private:
	GLFWwindow* m_window;
	int m_displayW;
	int m_displayH;
	unsigned m_shaderProgram;
};

