#pragma once
#include "Renderer.h"
#include "graphics.h"
#include <array>
#include <unordered_map>

class TextureManager {

private:
	unsigned int m_whiteTexture;
	std::array<uint8_t, 32>  m_textureSlots;

public:
	TextureManager();
	~TextureManager();
	static GLuint LoadTexture(const std::string& path);
	static std::unordered_map<std::string, GLuint> TextureCache;
};
