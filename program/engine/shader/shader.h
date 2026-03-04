#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Shader {
public:
    unsigned int ID;

    Shader(std::string& vertexPath, std::string& fragmentPath);

    void use();

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat2(const std::string& name, const glm::mat2& mat) const;
    void setMat3(const std::string& name, const glm::mat3& mat) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void setVi(const std::string& name, const int count, const int value[]) const;
    void setVec3(const std::string& name, const int count, const glm::vec3& vec) const;

private:
    GLuint createShader(std::string& path, GLenum type);
};
