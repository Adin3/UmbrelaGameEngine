#include "TextureManager.h"

std::unordered_map<std::string, GLuint> TextureManager::TextureCache;

TextureManager::TextureManager()
{
	glEnable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

TextureManager::~TextureManager()
{
	glDeleteTextures(1, &m_whiteTexture);
}

GLuint TextureManager::LoadTexture(const std::string& path)
{
	if (TextureCache.find(path) != TextureCache.end())
	{
		return TextureCache[path];
	}
	else
	{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int height, width, channels;
	stbi_set_flip_vertically_on_load(true);
	auto* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	TextureCache[path] = textureID;
	return textureID;
	}

}
