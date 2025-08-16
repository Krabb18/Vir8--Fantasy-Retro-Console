#version 430 core
out vec4 FragColor;

in vec3 color;

in vec2 texCoord;

in vec4 currentColor;

uniform sampler2D tex0;

void main()
{
FragColor = currentColor;
};