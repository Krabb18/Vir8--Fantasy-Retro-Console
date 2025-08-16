#include "RenderObj.h"

void RenderObj::Init()
{
	shader.Init("obj.vert", "obj.frag");

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
}

void RenderObj::Render()
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, scale);

	shader.Activate();

	glUniform4f(glGetUniformLocation(shader.ID, "col"), color.x, color.y, color.z, color.a);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"),1,GL_FALSE, glm::value_ptr(model));

	VAO1.Bind();
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);
}

void RenderObj::Delete()
{
	shader.Delete();
	VAO1.Delete();
}