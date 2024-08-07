#include "MinGL.h"
#include "glad.h" // OpenGL functions
#include "glfw3.h" // windows, contexts, input and events
#include <iostream>
#include <vector>

const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 inColor;\n"
"void main()\n"
"{\n"
"   FragColor = inColor;\n"
"}\0";

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool MinGL::init(unsigned width, unsigned height, const char* title)
{
	// GLFW
	//
	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return false;

	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!m_window)
	{
		fprintf(stderr, "Failed to create GLFW m_window\n");
		return false;
	}

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1); // Enable vsync
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

	// GLAD
	//
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		fprintf(stderr, "Failed to initialize GLAD\n");
		return false;
	}

	float vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f
	};

	unsigned VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer
	(
		0,					// Location = 0
		3,					// Size of vertex attribute
		GL_FLOAT,			// Type of the data
		GL_FALSE,			// Normalize data?
		3 * sizeof(float),	// Stride
		(void*)0			// Offset
	);
	glEnableVertexAttribArray(0/*Location*/);
	glBindVertexArray(0);

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		fprintf(stderr, infoLog);
		return false;
	}
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		fprintf(stderr, infoLog);
		return false;
	}

	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, vertexShader);
	glAttachShader(m_shaderProgram, fragmentShader);
	glLinkProgram(m_shaderProgram);
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_shaderProgram, 512, nullptr, infoLog);
		fprintf(stderr, infoLog);
		return false;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(m_shaderProgram);
	glBindVertexArray(VAO);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

bool MinGL::windowShouldClose() const
{
	return (bool)glfwWindowShouldClose(m_window);
}

void MinGL::pollEvents() const
{
	glfwPollEvents();
}

void MinGL::processInput() const
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);
}

void MinGL::putPixel(int x, int y, const MinGLColor& color, int width, int height) const
{
	GLint transformLoc = glGetUniformLocation(m_shaderProgram, "inColor");
	glUniform4f(transformLoc, color.rgba[0], color.rgba[1], color.rgba[2], color.rgba[3]);

	glEnable(GL_SCISSOR_TEST);
	glScissor(x, y, width, height); /// position of pixel
	glDrawArrays(GL_TRIANGLES, 0/*Starting Index*/, 6/*# of vertices*/);
	glDisable(GL_SCISSOR_TEST);
}

MinGLColor MinGL::getPixelColor(int x, int y) const{
	constexpr int pixelSize = 4; // RGBA has 4 components (R, G, B, A)
    std::vector<unsigned char> pixel(pixelSize);
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel.data());
	const MinGLColor color{(float)pixel[0]/255, (float)pixel[1]/255, (float)pixel[2]/255, 1.0f};
	return color;
}

void MinGL::drawLine(int x0, int y0, int x1, int y1, const MinGLColor& color) const{
	// Bresenham's line generation algorithm is used here

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

	const int dx = x1 - x0;
	const int dy = y1 - y0;

	int derror = std::abs(dy) * 2;
	int error = 0;
	int y = y0;
	for (int x = x0; x <= x1; ++x) {
		if (steep) {
			putPixel(y, x, color);
		}
		else {
			putPixel(x, y, color);
		}
		error += derror;
		if (error > dx) {
			y += (y1 > y0 ? 1 : -1);
			error -= dx * 2;
		}
	}
}
void MinGL::drawRectangle(int x0, int y0, int x1, int y1, const MinGLColor& color) const{
	// specify any two diagonally opposite points of the rectangle
	// draws a rectangle with sides parallel to screen

	const int xa = std::min(x0, x1);
	const int ya = std::min(y0, y1);

	const int xb = std::max(x0, x1);
	const int yb = std::max(y0, y1);

	for(int i=xa; i<xb; i++){
		putPixel(i, ya, color);
	}
	for(int i=ya; i<yb; i++){
		putPixel(xb, i, color);
	}
	for(int i=xb; i>xa; i--){
		putPixel(i, yb, color);
	}
	for(int i=yb; i>ya; i--){
		putPixel(xa, i, color);
	}
}


void MinGL::drawCircle(int xc, int yc, int rad, const MinGLColor& color) const{
	// specify center (x,y) of circle and its radius
	// Bresenham's circle drawing algorithm is used here

	auto draw = [this, xc, yc, &color](int x, int y){
		putPixel(xc+x, yc+y, color);
		putPixel(xc-x, yc+y, color);
		putPixel(xc+x, yc-y, color);
		putPixel(xc-x, yc-y, color);
		putPixel(xc+y, yc+x, color);
		putPixel(xc-y, yc+x, color);
		putPixel(xc+y, yc-x, color);
		putPixel(xc-y, yc-x, color);
	};

	int x = 0, y = rad;
    int d = 3 - 2 * rad;
	draw(x, y);

	while(y >= x){
        x++;
        if (d > 0){
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;

        draw(x, y);
    }
}

void MinGL::flush(float r, float g, float b, float a)
{
	glfwGetFramebufferSize(m_window, &m_displayW, &m_displayH);
	glfwSwapBuffers(m_window);
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void MinGL::flush(const MinGLColor& color)
{
	flush(color.rgba[0], color.rgba[1], color.rgba[2], color.rgba[3]);
}

void MinGL::shutdown() const
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

GLFWwindow* MinGL::getWindow()
{
	return m_window;
}
