#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "shaderClass.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"

#include "Console.h"

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


	// Blending aktivieren
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//Font und back buffer
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	Vir consoleVir;
	consoleVir.InitVir();


	//Loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		consoleVir.RenderVir();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window); 
	consoleVir.DeleteVir();

	glfwTerminate();
	return 0;
}