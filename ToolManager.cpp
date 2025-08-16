#include "ToolManager.h"

void ToolManager::Init()
{
    for(int i = 0; i<8; i++)
    {
        for(int j = 0; j<8; j++)
        {
            RenderObj renderObjInst;

            //if (j == 4) { renderObjInst.color = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f); }

            renderObjInst.position.x = (i * 0.1f) + spriteEditorPosition.x;
            renderObjInst.position.y = (j * 0.2f) + spriteEditorPosition.y;
            renderObjInst.scale.x = 0.1f;
            renderObjInst.scale.y = 0.2f;

            renderObjInst.Init();
            cells[i][j] = renderObjInst;
        }
    }

    //Man kann 30 sprites erstellen
    for(int i = 0; i<30; i++)
    {
        Sprite sprite;
        sprites.push_back(sprite);
    }

    mouse.scale.x = 0.01f;
    mouse.scale.y = 0.01f;
}

void ToolManager::Handle(GLFWwindow *window)
{
	ImGui::Begin("Tools");

	if(ImGui::BeginTabBar("Tabs"))
	{
        if (ImGui::BeginTabItem("Game"))
        {
            inGameMode = true;
            ImGui::EndTabItem();
        }
        else
        {
            inGameMode = false;
        }

        if (ImGui::BeginTabItem("Sprite Editor"))
        {
            SpriteEditorUI();
            SpriteEditor(window);

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
	}


	ImGui::End();
}

bool ToolManager::CheckCollisions(RenderObj& renderObj1, RenderObj& renderObj2)
{
    bool collisionX = renderObj1.position.x + renderObj1.scale.x >= renderObj2.position.x && renderObj2.position.x + renderObj2.scale.x >= renderObj1.position.x;
    bool collisionY = renderObj1.position.y + renderObj1.scale.y >= renderObj2.position.y && renderObj2.position.y + renderObj2.scale.y >= renderObj1.position.y;
    return collisionX && collisionY;
}

void ToolManager::Delete()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cells[i][j].Delete();
        }
    }
}

void ToolManager::SpriteEditorUI()
{
    ImVec4 blackCol = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    if (ImGui::ColorButton("Black", blackCol))
    {
        currentColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }

    ImGui::SameLine();

    ImVec4 redCol = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    if (ImGui::ColorButton("Red", redCol))
    {
        currentColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    }

    ImVec4 greenCol = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
    if (ImGui::ColorButton("Green", greenCol))
    {
        currentColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    }

    ImVec4 blueCol = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
    if (ImGui::ColorButton("Blue", blueCol))
    {
        currentColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    }

    ImVec4 alphaCol = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    if (ImGui::ColorButton("Alpha", alphaCol))
    {
        currentColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    }

}

void ToolManager::SpriteEditor(GLFWwindow* window)
{
    double mouseX = 0.0f;
    double mouseY = 0.0f;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    float ndcX = (2.0f * mouseX) / screenWidth - 1.0f;
    float ndcY = 1.0f - (2.0f * mouseY) / screenHeight;

    mouse.position.x = ndcX;
    mouse.position.y = ndcY;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(CheckCollisions(cells[i][j], mouse) && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            {
                sprites[currentSpriteIndex].colors[i][j] = currentColor;
                cells[i][j].color = sprites[currentSpriteIndex].colors[i][j];
            }

            cells[i][j].Render();
        }
    }
}
