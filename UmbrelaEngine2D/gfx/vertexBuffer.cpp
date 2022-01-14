#include "vertexBuffer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

vertexBuffer::vertexBuffer(const float* buffer, int size)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_DYNAMIC_DRAW);
}

vertexBuffer::~vertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void vertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void vertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vertexBuffer::SetData(void* buffer, int size)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, buffer);
}
