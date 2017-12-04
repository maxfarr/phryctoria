#pragma once

//first GLEW
#include <GL\glew.h>
//then GLFW
#include <GLFW\glfw3.h>
//and then GLM
#include <glm\glm.hpp>
using namespace glm;

#include <vector>

struct VertAttrib
{
public:
	GLint Size;
	GLenum Type;
	GLboolean Normalized;
	GLsizei Stride;
	const void* Offset;
	
	VertAttrib(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset);
};

class Mesh
{
public:
	const GLfloat* Data;
	std::vector<VertAttrib> Attributes;
	GLenum RenderMode;
	GLsizeiptr DataSize;
	GLint VertexCount;

	Mesh(GLenum renderMode, GLsizeiptr dataSize, GLint vertexCount);
	//~Mesh();

	void Bind();
	void Render();

private:
	GLuint VBO;
	GLuint VAO;

};