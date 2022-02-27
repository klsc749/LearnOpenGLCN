#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shaderToolCLass/shader.h"
void PrcocessInput(GLFWwindow* window);

int main()
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(640, 480, "Hello OpenGL", NULL, NULL);


	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);


	if (glewInit() != GLEW_OK)
	{
		return -1;
	}

	float vertices[] = {
		// positions         // colors
		 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // top right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // top left
		 0.5f,  -0.5f, 0.0f,  0.0f, 0.0f, 0.0f   // top right
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 1, 3
	};

	Shader program("res/shaders/basic.shader");
	program.Use();

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);


	while (!glfwWindowShouldClose(window))
	{
		//清理缓冲区
		glClearColor(0.4f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//处理输入
		PrcocessInput(window);
		

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//双缓存交换
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void PrcocessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}