#ifndef VIR_H
#define VIR_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "shaderClass.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"

#include "RenderObj.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include <sol/sol.hpp>

#include <vector>

using namespace std;

class Vir
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
	
	GLuint ssboScreenPixels;
	GLuint ssboScreenColors;

	vector<glm::mat4> pixelMats;
	vector<glm::vec4> pixelColors;
	

	glm::mat4 model = glm::mat4(1.0f);

	glm::vec4 backGroundColor = glm::vec4(1.0f);
	glm::vec4 screenBuffer[128][128];

	void BindSSBO();


	string scriptPath = "test.lua";
public:
	vector<Sprite> sprites;

	bool playMode = true;

	sol::state lua;

	Shader consoleShader;
	glm::vec3 screenPos = glm::vec3(-0.5f, -0.5f, 0.0f);

	void ClearScreen();
	void DrawScreenBuffer();

	void InitScriptReader();

	void DrawPixel(int posX, int posY, int r, int g, int b, int a);
	void DrawSprite(int spriteNum ,int posX, int posY); //Noch scale adden vielleciht

	void Start();
	void Update();

	void InitVir();
	void RenderVir();
	void DeleteVir();
};

#endif // !VIR_H
