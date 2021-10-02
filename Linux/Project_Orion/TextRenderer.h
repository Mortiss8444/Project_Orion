#pragma once
#include "shader.h"
namespace Project_Orion
{
	int LoadFont();
	void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);
}
