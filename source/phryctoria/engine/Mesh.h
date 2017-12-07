#pragma once

//first GLEW
#include <GL\glew.h>
//then GLFW
#include <GLFW\glfw3.h>
//and then GLM
#include <glm\glm.hpp>
using namespace glm;

#include <vector>

enum VertexMode
{
	RAW,
	INDEXED
};

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
	std::vector<GLfloat> Data;
	std::vector<GLuint> Indices;
	std::vector<VertAttrib> Attributes;
	GLenum RenderMode;
	VertexMode VertMode;
	GLint VertexCount;

	Mesh(GLenum renderMode, VertexMode vertMode, GLint vertexCount);
	//~Mesh();

	void LoadPointer(GLfloat* data, GLuint dataSize, GLuint* indices, GLuint indicesSize);
	void Bind();
	void Render();

private:
	GLuint VBO, VAO, EBO;

};