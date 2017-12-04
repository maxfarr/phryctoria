#include "Mesh.h"

VertAttrib::VertAttrib(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset)
{
	Size = size;
	Type = type;
	Normalized = normalized;
	Stride = stride;
	Offset = offset;
}

Mesh::Mesh(GLenum renderMode, GLsizeiptr dataSize, GLint vertexCount)
{
	RenderMode = renderMode;
	DataSize = dataSize;
	VertexCount = vertexCount;
}

void Mesh::Bind()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, DataSize, Data, GL_STATIC_DRAW);

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
}