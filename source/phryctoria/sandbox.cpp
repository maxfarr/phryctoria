#include <stdio.h>
#include <stdlib.h>

//first GLEW
#include <GL\glew.h>
//then GLFW
#include <GLFW\glfw3.h>
//and then GLM
#include <glm\glm.hpp>
using namespace glm;

#include "..\..\stb\stb_image.h"

#include "shaders\LoadShader.cpp"

#include "engine\Mesh.h"

GLFWwindow* window;

int main()
{
	if (!glfwInit())
	{
		fprintf(stderr, "GLFW failed to initialize\n");
		return -1;
	}

	//GLFW version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//GLFW settings
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //potential osx port?

	window = glfwCreateWindow(1024, 768, "OpenGL Sandbox", NULL, NULL);
	if (window == NULL)
	{
		fprintf(stderr, "GLFW failed to open a window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//GLEW init
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "GLEW failed to initialize\n");
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint programID = LoadShader("shaders/source/simple.vert", "shaders/source/simple.frag");

	static GLfloat vertexData[] = {
		0.5f,  0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	static GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	Mesh triangle(GL_TRIANGLES, sizeof(indices));
	triangle.Attributes.push_back(VertAttrib(3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	/*triangle.Attributes.push_back(VertAttrib(3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));*/
	triangle.LoadPointer(&vertexData[0], sizeof(vertexData), &indices[0], sizeof(indices));

	triangle.Bind();

	glUseProgram(programID);

	do
	{
		glClear(GL_COLOR_BUFFER_BIT);

		triangle.Render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}