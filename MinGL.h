#pragma once

struct GLFWwindow;

struct MinGLColor
{
	float rgba[4] = { 0,0,0,0 };
};

class MinGL
{
public:
	bool init(unsigned width, unsigned height, const char* title);
	bool windowShouldClose() const;
	void pollEvents() const;
	void processInput() const;
	void putPixel(int x, int y, const MinGLColor& color, int width=1, int height=1) const;
	void flush(float r, float g, float b, float a);
	void flush(const MinGLColor& color);
	void shutdown() const;
	GLFWwindow* getWindow();

private:
	GLFWwindow* m_window;
	int m_displayW;
	int m_displayH;
	unsigned m_shaderProgram;
};
