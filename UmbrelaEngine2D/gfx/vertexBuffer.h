#pragma once


class vertexBuffer {
private:
	unsigned int m_RendererID;
public:
	vertexBuffer(const float* buffer, int size);
	~vertexBuffer();
	void Bind();
	void Unbind();
	void SetData(void* buffer, int size);
};