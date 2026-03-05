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
	auto* data = stbi_load(path.c_str(), &width, &height, &channels, 4);
	if (data) {

		GLenum format = GL_RGBA;
		// This is actual hell, i will force data to hold 4 channels for the time being
		/*if (channels == 1)
			format = GL_RED;
		else if (channels == 3)
			format = GL_RGB;
		else if (channels == 4)
			format = GL_RGBA;*/

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else std::cout << "TEXTURE NOT FOUND - " + path << std::endl;
	if (stbi_failure_reason()) {

		std::cout << stbi_failure_reason(); std::cout << path<<std::endl;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	TextureCache[path] = textureID;
	return textureID;
	}

}
