//LIGHT FRAGMENT SHADER

#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D tex;

void main()
{   
    vec3 color = vec3(0.8, 0.8, 0.8) * vec3(texture(tex, TexCoords));
    FragColor = vec4(color, 1.0);
}