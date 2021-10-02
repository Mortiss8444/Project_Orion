#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "shader.h"

namespace Project_Orion {
	class Texture
	{
	public:
		GLuint ID;
		GLenum type;
		Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

		// Assigns a texture unit to a texture
		void texUnit(Shader& shader, const char* uniform, GLuint unit);
		// Binds a texture
		void Bind();
		// Unbinds a texture
		void Unbind();
		// Deletes a texture
		void Delete();
	};
}