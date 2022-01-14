#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoords;

out vec2 ourTexCoords;
out vec4 ourColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;

void main()
{
    gl_Position = model * vec4(aPos, 1.0);
	ourTexCoords = aTexCoords;
	ourColor = aColor;
}