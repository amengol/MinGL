#include "MinGL.h"
#include <glad/glad.h> // OpenGL functions
#include <GLFW/glfw3.h> // windows, contexts, input and events
#include <iostream>

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

void MinGL::putPixel(int x, int y, float r, float g, float b) const
{
	glEnable(GL_SCISSOR_TEST);
	glScissor(x, y, 1, 1); /// position of pixel
	glClearColor(r, g, b, 0.0f); /// color of pixel
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);
}

void MinGL::flush(float r, float g, float b, float a)
{
	glfwGetFramebufferSize(m_window, &m_displayW, &m_displayH);
	glfwSwapBuffers(m_window);
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
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
