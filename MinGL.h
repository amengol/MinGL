#pragma once
struct GLFWwindow;

class MinGL
{
public:
	bool init(unsigned width, unsigned height, const char* title);
	bool windowShouldClose() const;
	void pollEvents() const;
	void processInput() const;
	void putPixel(int x, int y, float r, float g, float b) const;
	void flush(float r, float g, float b, float a);
	void shutdown() const;
	GLFWwindow* getWindow();

private:
	GLFWwindow* m_window;
	int m_displayW;
	int m_displayH;
};

