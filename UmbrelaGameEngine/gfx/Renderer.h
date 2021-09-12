#pragma once
#include "TextureManager.h"
#include "graphics.h"

class TextureManager;

class Renderer {
private:

public:
	Renderer();
	~Renderer();
	void Draw(glm::mat4 view);
	void Clear();
	static void BeginBatch();
	static void EndBatch();

	static void CreateQuad(const glm::vec2& size, const glm::vec2& position, const glm::vec3& color);
	static void CreateQuad(const glm::vec2& size, const glm::vec2& position, const unsigned int& textureID, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
protected:

	static std::shared_ptr<TextureManager> texture;
	static std::shared_ptr<vertexArray> VAO;
	static std::shared_ptr<vertexBuffer> VBO;
	static std::shared_ptr<indexBuffer> EBO;
	static std::shared_ptr<Shader> shader;
};