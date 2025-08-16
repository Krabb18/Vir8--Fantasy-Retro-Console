#version 430 core
out vec4 FragColor;

in vec3 color;

in vec2 texCoord;


uniform sampler2D tex0;
uniform vec4 col;

void main()
{
FragColor = col;
};