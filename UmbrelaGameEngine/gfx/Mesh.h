#pragma once
#include "graphics.h"
#include <string>
#include <vector>
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 Texcoords;
};

struct Texture {
	unsigned int  id;
	std::string type;
};

class Mesh {
private:
	unsigned int VAO, VBO, EBO;

	void setupMesh();

public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader& shader);
};