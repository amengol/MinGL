#pragma once
#include<math.h>

struct GLFWwindow;

struct MinGLColor
{
	float rgba[4] = { 0,0,0,0 };

	float epsilon = 0.0039215;
	bool operator == (const MinGLColor color2) const{
		for(int i=0; i<4; i++){
			if( fabs(this->rgba[i] - color2.rgba[i]) > epsilon )return false;
		}
		return true;
	}
	bool operator != (const MinGLColor color2) const{
		return !(*this==color2);
	}
};

class MinGL
{
public:
	bool init(unsigned width, unsigned height, const char* title);
	bool windowShouldClose() const;
	void pollEvents() const;
	void processInput() const;
	void putPixel(int x, int y, const MinGLColor& color, int width=1, int height=1) const;
	const MinGLColor getPixelColor(int x, int y) const;
	void drawLine(int x0, int y0, int x1, int y1, const MinGLColor& color);
	void drawRectangle(int x0, int y0, int x1, int y1, const MinGLColor& color);
	void drawCircle(int x, int y, int rad, const MinGLColor& color);
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
