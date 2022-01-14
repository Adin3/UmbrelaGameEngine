#include "vertexArray.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

vertexArray::vertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);
}

vertexArray::~vertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void vertexArray::Bind()
{
	glBindVertexArray(m_RendererID);
}

void vertexArray::Unbind()
{
	glBindVertexArray(0);
}
