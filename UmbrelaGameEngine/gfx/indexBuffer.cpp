#include "indexBuffer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

indexBuffer::indexBuffer(const unsigned int* buffer, unsigned int count) :m_Count(count)
{
	glGenBuffers(1, &m_RenderedID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderedID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GL_UNSIGNED_INT), buffer, GL_STATIC_DRAW);
}

indexBuffer::~indexBuffer()
{
	glDeleteBuffers(1, &m_RenderedID);
}

void indexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderedID);
}

void indexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int indexBuffer::GetCount()
{
	return m_Count;
}
