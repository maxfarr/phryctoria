#include <stdio.h>
#include <stdlib.h>

//first GLEW
#include <GL\glew.h>
//then GLFW
#include <GLFW\glfw3.h>
//and then GLM
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
using namespace glm;

#include "..\..\stb\stb_image.h"

#include "shaders\LoadShader.cpp"

#include "engine\Mesh.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

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

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Sandbox", NULL, NULL);
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
	
	//configure opengl
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint programID = LoadShader("shaders/source/simpletransform.vert", "shaders/source/simpletransform.frag");

	static GLfloat cubeVertexData[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	};

	static GLfloat rawCubeVertexData[] =
	{
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	static GLuint indices[] = {
		0, 1, 2,
		2, 0, 3,

		4, 5, 6,
		6, 4, 7,

		8, 9, 10,
		10, 8, 11,

		12, 13, 14,
		14, 12, 15,

		16, 17, 18,
		18, 16, 19,

		20, 21, 22,
		22, 20, 23
	};

	Mesh triangle(GL_TRIANGLES, RAW, 36);
	triangle.Attributes.push_back(VertAttrib(3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0));
	triangle.Attributes.push_back(VertAttrib(2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));
	triangle.LoadPointer(&rawCubeVertexData[0], sizeof(rawCubeVertexData), NULL, 0);

	triangle.Bind();

	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, channelCount;
	unsigned char *data = stbi_load("../../resources/crate2.png", &width, &height, &channelCount, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Loading texture failed" << std::endl;
	}

	stbi_image_free(data);

	glUseProgram(programID);

	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//to-do: model matrix should be part of component class
		mat4 model = mat4(1.0f);
		model = rotate(model, (float)glfwGetTime() * radians(50.0f), vec3(0.5f, 1.0f, 0.0f));

		//to-do: make view and projection matrices part of camera class
		mat4 view = mat4(1.0f);
		view = translate(view, vec3(0.0f, 0.0f, -3.0f));

		mat4 projection = mat4(1.0f);
		projection = perspective(radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		
		unsigned int modelLocation = glGetUniformLocation(programID, "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));

		unsigned int viewLocation = glGetUniformLocation(programID, "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(view));

		unsigned int projectionLocation = glGetUniformLocation(programID, "projection");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projection));

		glBindTexture(GL_TEXTURE_2D, tex);
		triangle.Render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window));
}