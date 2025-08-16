#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "shaderClass.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Console.h"
#include "ToolManager.h"

using namespace std;

int screenWidth = 0;
int screenHeight = 0;

int main()
{
	glfwInit();
	

	//initialisiere anderen kak
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//Initialisiere das fenster
	auto monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	screenWidth = mode->width;
	screenHeight = mode->height;
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Vir8", NULL, NULL);
	if(window == NULL)
	{
		glfwTerminate();
		cout << "Hat nicht geklappt ohoh" << endl;
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, screenWidth, screenHeight);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");



	// Blending aktivieren
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//Font und back buffer
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	Vir consoleVir;
	consoleVir.InitVir();
	consoleVir.InitScriptReader();
	consoleVir.Start();

	ToolManager toolManager;
	toolManager.screenWidth = screenWidth;
	toolManager.screenHeight = screenHeight;
	toolManager.Init();

	//Loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//consoleVir.RenderVir();
		if(toolManager.inGameMode)
		{
			consoleVir.RenderVir();
		}

		toolManager.Handle(window);
		//toolManager.SpriteEditor(window);

		consoleVir.sprites = toolManager.sprites;
		

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window); 
	consoleVir.DeleteVir();
	toolManager.Delete();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}