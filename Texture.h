#pragma once
#include<glad/glad.h>
#include<stb/stb_image.h>
#include"shaderClass.h"

class Texture {
public:
	GLuint ID;
	GLenum type;

	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
		type = texType;
		int widthImg, heightImg, numColCh;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

		glGenTextures(1, &ID);
		glActiveTexture(slot);
		glBindTexture(texType, ID);

		glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
		glGenerateMipmap(texType);

		stbi_image_free(bytes);
		glBindTexture(texType, 0);
	}

	void texUnit(Shader& shader, const char* uniform, GLuint unit) {
		GLuint texUni = glGetUniformLocation(shader.ID, uniform);
		shader.Activate();
		glUniform1i(texUni, unit);
	}

	void Bind() {
		glBindTexture(type, ID);
	}

	void Unbind() {
		glBindTexture(type, 0);
	}

	void Delete() {
		glDeleteTextures(1, &ID);
	}
};