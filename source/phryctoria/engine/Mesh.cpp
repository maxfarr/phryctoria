#include "Mesh.h"

VertAttrib::VertAttrib(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset)
{
	Size = size;
	Type = type;
	Normalized = normalized;
	Stride = stride;
	Offset = offset;
}

Mesh::Mesh(GLenum renderMode, GLint vertexCount)
{
	RenderMode = renderMode;
	VertexCount = vertexCount;
}

void Mesh::LoadPointer(GLfloat* data, GLuint dataSize, GLuint* indices, GLuint indicesSize)
{
	for (uint i = 0; i < dataSize; i++)
	{
		Data.push_back(data[i]);
	}

	for (uint i = 0; i < indicesSize; i++)
	{
		Indices.push_back(indices[i]);
	}
}

void Mesh::Bind()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Data.size(), &Data[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), &Indices[0], GL_STATIC_DRAW);

	for (int i = 0; i < Attributes.size(); i++)
	{
		glVertexAttribPointer(i, Attributes[i].Size, Attributes[i].Type, Attributes[i].Normalized, Attributes[i].Stride, Attributes[i].Offset);
		glEnableVertexAttribArray(i);
	}
}

void Mesh::Render()
{
	glBindVertexArray(VAO);
	glDrawArrays(RenderMode, 0, VertexCount);
	glDrawElements(GL_TRIANGLES, VertexCount, GL_UNSIGNED_INT, 0);
}