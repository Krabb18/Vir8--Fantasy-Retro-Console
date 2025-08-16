#version 430 core

//Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

// Outputs the color for the Fragment Shader
out vec3 color;

out vec2 texCoord;

// Controls the scale of the vertices
uniform mat4 model;


void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = model * vec4(aPos, 1.0);
	
	color = aColor;
	texCoord = aTex;
}