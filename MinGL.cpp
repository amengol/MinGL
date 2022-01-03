#include "MinGL.h"
#include <glad/glad.h> // OpenGL functions
#include <GLFW/glfw3.h> // windows, contexts, input and events
#include <iostream>

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

void MinGL::putPixel(int x, int y, const MinGLColor& color) const
{
	GLint transformLoc = glGetUniformLocation(m_shaderProgram, "inColor");
	glUniform4f(transformLoc, color.rgba[0], color.rgba[1], color.rgba[2], color.rgba[3]);

	glEnable(GL_SCISSOR_TEST);
	glScissor(x, y, 1, 1); /// position of pixel
	glDrawArrays(GL_TRIANGLES, 0/*Starting Index*/, 6/*# of vertices*/);
	glDisable(GL_SCISSOR_TEST);
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
