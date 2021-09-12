#pragma once

class vertexArray {
private:
	unsigned int m_RendererID;
public:

	vertexArray();
	~vertexArray();
	void Bind();
	void Unbind();
};