#ifndef RENDEROBJ_H
#define RENDEROBJ_H

#include "shaderClass.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

struct Sprite
{
	glm::vec4 colors[8][8];
};

class RenderObj
{
private:
	// Vertices coordinates
	GLfloat vertices[32] =
	{ //     COORDINATES     /        COLORS      /   TexCoord  //
		-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
		-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
		 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
		 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
	};

	// Indices for vertices order
	GLuint indices[6] =
	{
		0, 2, 1, // Upper triangle
		0, 3, 2 // Lower triangle
	};

	VAO VAO1;

public:
	glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f,1.0f);

	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(0.5, 1.0f, 0.0f);

	Shader shader;
	void Init();
	void Render();
	void Delete();
};

#endif // !RENDEROBJ_H
