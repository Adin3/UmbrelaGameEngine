#version 450 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in float aTexIndex;

out vec4 vColor;
out vec2 vTexCoords;
out flat float vTexIndex;
//uniform mat4 model;
uniform mat4 pv;

void main()
{
	gl_Position = pv * aPos;
	vTexCoords = aTexCoords;
	vTexIndex = aTexIndex;
	vColor = aColor;
}