// MeshPrimitives.h
#pragma once
#include "Mesh.h"
#include "TextureManager.h"
#include "../engine/src/Path.h"

class MeshPrimitives
{
public:
    static Mesh CreateCube(float halfExtent = 0.5f)
    {
        std::vector<Vertex> vertices =
        {
            // Front
            { glm::vec3(-halfExtent, -halfExtent,  halfExtent), glm::vec3(0, 0, 1), glm::vec2(0, 0) },
            { glm::vec3(halfExtent, -halfExtent,  halfExtent), glm::vec3(0, 0, 1), glm::vec2(1, 0) },
            { glm::vec3(halfExtent,  halfExtent,  halfExtent), glm::vec3(0, 0, 1), glm::vec2(1, 1) },
            { glm::vec3(-halfExtent,  halfExtent,  halfExtent), glm::vec3(0, 0, 1), glm::vec2(0, 1) },
            // Back
            { glm::vec3(halfExtent, -halfExtent, -halfExtent), glm::vec3(0, 0, -1), glm::vec2(0, 0) },
            { glm::vec3(-halfExtent, -halfExtent, -halfExtent), glm::vec3(0, 0, -1), glm::vec2(1, 0) },
            { glm::vec3(-halfExtent,  halfExtent, -halfExtent), glm::vec3(0, 0, -1), glm::vec2(1, 1) },
            { glm::vec3(halfExtent,  halfExtent, -halfExtent), glm::vec3(0, 0, -1), glm::vec2(0, 1) },
            // Left
            { glm::vec3(-halfExtent, -halfExtent, -halfExtent), glm::vec3(-1, 0, 0), glm::vec2(0, 0) },
            { glm::vec3(-halfExtent, -halfExtent,  halfExtent), glm::vec3(-1, 0, 0), glm::vec2(1, 0) },
            { glm::vec3(-halfExtent,  halfExtent,  halfExtent), glm::vec3(-1, 0, 0), glm::vec2(1, 1) },
            { glm::vec3(-halfExtent,  halfExtent, -halfExtent), glm::vec3(-1, 0, 0), glm::vec2(0, 1) },
            // Right
            { glm::vec3(halfExtent, -halfExtent,  halfExtent), glm::vec3(1, 0, 0), glm::vec2(0, 0) },
            { glm::vec3(halfExtent, -halfExtent, -halfExtent), glm::vec3(1, 0, 0), glm::vec2(1, 0) },
            { glm::vec3(halfExtent,  halfExtent, -halfExtent), glm::vec3(1, 0, 0), glm::vec2(1, 1) },
            { glm::vec3(halfExtent,  halfExtent,  halfExtent), glm::vec3(1, 0, 0), glm::vec2(0, 1) },
            // Top
            { glm::vec3(-halfExtent,  halfExtent,  halfExtent), glm::vec3(0, 1, 0), glm::vec2(0, 0) },
            { glm::vec3(halfExtent,  halfExtent,  halfExtent), glm::vec3(0, 1, 0), glm::vec2(1, 0) },
            { glm::vec3(halfExtent,  halfExtent, -halfExtent), glm::vec3(0, 1, 0), glm::vec2(1, 1) },
            { glm::vec3(-halfExtent,  halfExtent, -halfExtent), glm::vec3(0, 1, 0), glm::vec2(0, 1) },
            // Bottom
            { glm::vec3(-halfExtent, -halfExtent, -halfExtent), glm::vec3(0, -1, 0), glm::vec2(0, 0) },
            { glm::vec3(halfExtent, -halfExtent, -halfExtent), glm::vec3(0, -1, 0), glm::vec2(1, 0) },
            { glm::vec3(halfExtent, -halfExtent,  halfExtent), glm::vec3(0, -1, 0), glm::vec2(1, 1) },
            { glm::vec3(-halfExtent, -halfExtent,  halfExtent), glm::vec3(0, -1, 0), glm::vec2(0, 1) },
        };

        std::vector<unsigned int> indices =
        {
            0,  1,  2,  2,  3,  0,  // Front
            4,  5,  6,  6,  7,  4,  // Back
            8,  9,  10, 10, 11, 8,  // Left
            12, 13, 14, 14, 15, 12, // Right
            16, 17, 18, 18, 19, 16, // Top
            20, 21, 22, 22, 23, 20  // Bottom
        };

        std::vector<Texture> textures = {
            {TextureManager::LoadTexture(TEXTURE("grid.jpeg")), "texture_diffuse"},
        };

        return Mesh(vertices, indices, textures);
    }

    static Mesh CreatePlane(float halfExtent = 10.0f)
    {
        std::vector<Vertex> vertices =
        {
            { glm::vec3(-halfExtent, 0, -halfExtent), glm::vec3(0, 1, 0), glm::vec2(0, 0) },
            { glm::vec3(halfExtent, 0, -halfExtent), glm::vec3(0, 1, 0), glm::vec2(5, 0) },
            { glm::vec3(halfExtent, 0,  halfExtent), glm::vec3(0, 1, 0), glm::vec2(5, 5) },
            { glm::vec3(-halfExtent, 0,  halfExtent), glm::vec3(0, 1, 0), glm::vec2(0, 5) },
        };

        std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };

        std::vector<Texture> textures = {
            {TextureManager::LoadTexture(TEXTURE("grid.jpeg")), "texture_diffuse"},
        };

        return Mesh(vertices, indices, textures);
    }
};