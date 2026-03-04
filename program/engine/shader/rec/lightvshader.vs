//LIGHT VERTEX SHADER

#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;

void main()
{
    mat4 mvp = perspective * view * model;
    gl_Position = mvp * vec4(aPos, 1.0);
}