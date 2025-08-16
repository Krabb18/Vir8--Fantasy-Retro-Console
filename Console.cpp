#include "Console.h"

void Vir::InitVir()
{
	consoleShader.Init("default.vert", "default.frag");

	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	VBO1.Delete();
	EBO1.Delete();

	//Screen ssbos
	glGenBuffers(1, &ssboScreenPixels);
	glGenBuffers(1, &ssboScreenColors);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboScreenPixels);
	size_t pixelMatSSBO = pixelMats.size() * sizeof(glm::mat4);
	glBufferData(GL_SHADER_STORAGE_BUFFER, pixelMatSSBO, pixelMats.data(), GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssboScreenPixels);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboScreenColors);
	size_t pixelColsSSBO = pixelColors.size() * sizeof(glm::vec4);
	glBufferData(GL_SHADER_STORAGE_BUFFER, pixelColsSSBO, pixelColors.data(), GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssboScreenColors);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.025f, 0.05f, 1.0f));

	pixelMats.push_back(model);
	pixelColors.push_back(glm::vec4(1.0, 0.0, 0.0, 1.0));

}

void Vir::BindSSBO()
{
	consoleShader.Activate();

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboScreenPixels);
	size_t pixelMatSSBO = pixelMats.size() * sizeof(glm::mat4);
	glBufferData(GL_SHADER_STORAGE_BUFFER, pixelMatSSBO, pixelMats.data(), GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssboScreenPixels);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboScreenColors);
	size_t pixelColsSSBO = pixelColors.size() * sizeof(glm::vec4);
	glBufferData(GL_SHADER_STORAGE_BUFFER, pixelColsSSBO, pixelColors.data(), GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssboScreenColors);
}

void Vir::RenderVir()
{
	ClearScreen();
	consoleShader.Activate();

	if (playMode) { Update(); }

	DrawScreenBuffer();

	BindSSBO();
	VAO1.Bind();

	glDrawElementsInstanced(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0, pixelMats.size());
}

void Vir::DeleteVir()
{
	VAO1.Delete();
	consoleShader.Delete();
	glDeleteBuffers(1, &ssboScreenPixels);
	glDeleteBuffers(1, &ssboScreenColors);

	pixelMats.clear();
	pixelColors.clear();
}


//Screen Functiosn
void Vir::ClearScreen()
{
	pixelMats.clear();
	pixelColors.clear();
	for(int i = 0; i<128; i++)
	{
		for(int j = 0; j<128; j++)
		{
			screenBuffer[i][j] = backGroundColor;
		}
	}
}

void Vir::DrawScreenBuffer()
{
	for(int i = 0; i<128; i++)
	{
		for(int j = 0; j<128; j++)
		{
			float xPos = (i * 0.007f) + screenPos.x;
			float yPos = (j * 0.01f) + screenPos.y;

			//if (j == 100) { screenBuffer[i][j] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); }

			glm::mat4 pixelMatInst = glm::mat4(1.0f);
			pixelMatInst = glm::translate(pixelMatInst, glm::vec3(xPos, yPos, 0.0f));
			pixelMatInst = glm::scale(pixelMatInst, glm::vec3(0.007f, 0.01f, 0.0f));

			pixelMats.push_back(pixelMatInst);
			pixelColors.push_back(screenBuffer[i][j]);
		}
	}
}