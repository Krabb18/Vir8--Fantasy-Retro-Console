#ifndef TOOLMANAGER_H
#define TOOLMANAGER_H

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "RenderObj.h"
#include <vector>

using namespace std;

class ToolManager
{
private:
	glm::vec3 spriteEditorPosition = glm::vec3(-0.4f, -0.5f, 0.0f);
	bool CheckCollisions(RenderObj& renderObj1, RenderObj& renderObj2);
	RenderObj mouse;

	int currentSpriteIndex = 0;
	glm::vec4 currentColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

public:
	float screenWidth = 0.0f;
	float screenHeight = 0.0f;
	RenderObj cells[8][8];

	bool inGameMode = false;

	void Init();
	void Handle(GLFWwindow* window);
	void Delete();

	vector<Sprite> sprites;
	void SpriteEditorUI();
	void SpriteEditor(GLFWwindow *window);
};

#endif // !TOOLMANAGER_H
