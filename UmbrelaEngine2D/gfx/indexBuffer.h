#pragma once

class indexBuffer {
private:
	unsigned int m_RenderedID;
	unsigned int m_Count;
public:
	indexBuffer(const unsigned int* buffer, unsigned int count);
	~indexBuffer();
	void Bind();
	void Unbind();
	unsigned int GetCount();
};