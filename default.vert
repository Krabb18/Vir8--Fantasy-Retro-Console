#version 430 core

//Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

// Outputs the color for the Fragment Shader
out vec3 color;

out vec2 texCoord;
out vec4 currentColor;

// Controls the scale of the vertices
uniform mat4 model;


layout(binding = 0, std430) buffer ModelMatrixDataJa {
    mat4 modelMatrices[];
};

layout(binding = 1, std430) buffer ModelIDs {
    vec4 IDs[];
};


void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = modelMatrices[gl_InstanceID] * vec4(aPos, 1.0);
	
	currentColor = IDs[gl_InstanceID];
	color = aColor;
	texCoord = aTex;
}