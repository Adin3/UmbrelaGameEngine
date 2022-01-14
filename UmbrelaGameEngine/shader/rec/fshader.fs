#version 450 core
out vec4 FragColor;

in vec2 ourTexCoords;
in vec4 ourColor;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture1;

void main()
{
    FragColor = texture(ourTexture, ourTexCoords);
}