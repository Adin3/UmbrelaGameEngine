#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "graphics.h"
#include "Mesh.h"
class Model
{
public:
    std::string directory;
    std::vector<Mesh> meshes;
    std::vector<Texture> textures_loaded;
    Model(const char* path)
    {
        loadModel(path);
    }
    void Draw(std::shared_ptr<Shader>& shader);
private:
    // model data

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
       std::string typeName);
};