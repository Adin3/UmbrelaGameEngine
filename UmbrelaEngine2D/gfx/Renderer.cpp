#include <memory>
#include "graphics.h"
#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <chrono>

std::shared_ptr<TextureManager> Renderer::texture;
std::shared_ptr<vertexArray>    Renderer::VAO;
std::shared_ptr<vertexBuffer>   Renderer::VBO;
std::shared_ptr<indexBuffer>    Renderer::EBO;
std::shared_ptr<Shader>         Renderer::shader;

const unsigned int NumberOfQuad = 1000;
const unsigned int maxIndices = NumberOfQuad * 6;
const unsigned int maxVertices = NumberOfQuad * 4;

glm::vec4 pos[4] = {
	{-0.5f, -0.5f, 0.0f, 1.0f},
	{-0.5f,  0.5f, 0.0f, 1.0f},
	{ 0.5f,  0.5f, 0.0f, 1.0f},
	{ 0.5f, -0.5f, 0.0f, 1.0f},
};


struct Vertex {
	glm::vec4 Position;
	glm::vec4 Color;
	glm::vec2 TexCoords;
	float TextureID;
};

struct RendererData {
	Vertex* rendererBufferptr = nullptr;
	Vertex* rendererBuffer = nullptr;
	unsigned int indicesCount = 0;
	unsigned int textureCount = 1;
	unsigned int m_whiteTexture;
	std::array<unsigned, 32>  m_textureSlots;
}s_data;

float randNum(int min, int max)
{
	float rn = rand() % max + min;
	return rn / 255.0f;
}

void Renderer::CreateQuad(const glm::vec2 &size, const glm::vec2 &position,  const glm::vec3 &color)
{
	if (s_data.indicesCount >= maxIndices)
	{
		EndBatch();
		BeginBatch();
	}

	float textureID = 0.0f;


	glm::mat4 secx;
	secx = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
	secx *= glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0));
	s_data.rendererBufferptr->Position = secx * pos[0];
	s_data.rendererBufferptr->Color = {color, 1.0f };
	s_data.rendererBufferptr->TexCoords = {0.0f, 0.0f};
	s_data.rendererBufferptr->TextureID = textureID;
	s_data.rendererBufferptr++;

	s_data.rendererBufferptr->Position = secx * pos[1];
	s_data.rendererBufferptr->Color = {color, 1.0f };
	s_data.rendererBufferptr->TexCoords = { 0.0f, 1.0f };
	s_data.rendererBufferptr->TextureID = textureID;
	s_data.rendererBufferptr++;

	s_data.rendererBufferptr->Position = secx * pos[2];
	s_data.rendererBufferptr->Color = {color, 1.0f };
	s_data.rendererBufferptr->TexCoords = { 1.0f, 1.0f };
	s_data.rendererBufferptr->TextureID = textureID;
	s_data.rendererBufferptr++;
	
	s_data.rendererBufferptr->Position = secx * pos[3];
	s_data.rendererBufferptr->Color = {color, 1.0f };
	s_data.rendererBufferptr->TexCoords = { 1.0f, 0.0f };
	s_data.rendererBufferptr->TextureID = textureID;
	s_data.rendererBufferptr++;

	s_data.indicesCount += 6;
}

void Renderer::CreateQuad(const glm::vec2& size, const glm::vec2& position, const unsigned int& textureID, const glm::vec4& color)
{
	if (s_data.indicesCount >= maxIndices || s_data.textureCount >= 31)
	{
		EndBatch();
		BeginBatch();
	}
	float index = 0;
	for (int i = 1; i < s_data.textureCount; i++)
	{
		if (s_data.m_textureSlots[i] == textureID)
		{
			index = i;
			break;
		}
	}

	if (index == 0)
	{
		s_data.m_textureSlots[s_data.textureCount] = textureID;
		index = (float)s_data.textureCount;
		s_data.textureCount++;
	}

	glm::vec4 colour = { 0.16f, 0.03f, 0.25f, 1.0f };
	glm::mat4 secx;
	secx = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
	secx *= glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0));
	s_data.rendererBufferptr->Position = secx * pos[0];
	s_data.rendererBufferptr->Color = color;
	s_data.rendererBufferptr->TexCoords = { 0.0f, 0.0f };
	s_data.rendererBufferptr->TextureID = index;
	s_data.rendererBufferptr++;

	s_data.rendererBufferptr->Position = secx * pos[1];
	s_data.rendererBufferptr->Color = color;
	s_data.rendererBufferptr->TexCoords = { 0.0f, 1.0f };
	s_data.rendererBufferptr->TextureID = index;
	s_data.rendererBufferptr++;

	s_data.rendererBufferptr->Position = secx * pos[2];
	s_data.rendererBufferptr->Color = color;
	s_data.rendererBufferptr->TexCoords = { 1.0f, 1.0f };
	s_data.rendererBufferptr->TextureID = index;
	s_data.rendererBufferptr++;

	s_data.rendererBufferptr->Position = secx * pos[3];
	s_data.rendererBufferptr->Color = color;
	s_data.rendererBufferptr->TexCoords = { 1.0f, 0.0f };
	s_data.rendererBufferptr->TextureID = index;
	s_data.rendererBufferptr++;

	s_data.indicesCount += 6;
}

Renderer::Renderer()
{
	srand(time(NULL));
	s_data.rendererBuffer = new Vertex[maxVertices];
	shader = std::make_shared<Shader>("gfx/shader/rec/vshader.vs", "gfx/shader/rec/fshader.fs");
	
	int sampler[32];
	for (int i = 0; i < 32; i++) sampler[i] = i;
	shader->use();
	shader->setVi("u_TextureUnit", 32, sampler);

	unsigned int indices[maxIndices];
	unsigned int offset = 0;
	for (int i = 0; i < maxIndices; i += 6)
	{
		indices[i+0] = 0 + offset;
		indices[i+1] = 1 + offset;
		indices[i+2] = 2 + offset;

		indices[i+3] = 2 + offset;
		indices[i+4] = 0 + offset;
		indices[i+5] = 3 + offset;
		offset += 4;
	}
	VAO = std::make_shared<vertexArray>();
	VBO = std::make_shared<vertexBuffer>(nullptr, sizeof(Vertex) * maxVertices);
	EBO = std::make_shared<indexBuffer>(indices, maxIndices);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)offsetof(Vertex, Position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)offsetof(Vertex, Color));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)offsetof(Vertex, TextureID));
	glEnableVertexAttribArray(3);
}

Renderer::~Renderer()
{
	delete[] s_data.rendererBuffer;
}

void Renderer::Draw(glm::mat4 view)
{
	//BeginBatch();
	shader->use();

	glm::mat4 perspective = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	shader->setMat4("pv", view);

	//CreateQuad({ 0.0, -0.25}, s_data.padoru);
	//CreateQuad({ 650, 500 }, s_data.padoru1);
	//EndBatch();
}

void Renderer::Clear()
{
	//glClearColor(0.12f, 0.72f, 0.72f, 0.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::BeginBatch()
{
	s_data.rendererBufferptr = s_data.rendererBuffer;
	s_data.indicesCount = 0;
	s_data.textureCount = 1;
	s_data.m_textureSlots.fill(0);
}

void Renderer::EndBatch()
{
	shader->use();
	for (int i = 1; i < s_data.textureCount; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, s_data.m_textureSlots[i]);
	}
	GLsizeiptr size = (uint8_t*)s_data.rendererBufferptr - (uint8_t*)s_data.rendererBuffer;
	VBO->SetData(s_data.rendererBuffer, (uint32_t)size);
	VAO->Bind();
	glDrawElements(GL_TRIANGLES, s_data.indicesCount, GL_UNSIGNED_INT, NULL);
}