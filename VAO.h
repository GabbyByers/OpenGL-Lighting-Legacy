#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO {
public:
	// ID reference for the Vertex Array Object
	GLuint ID;

	// Constructor that generates a VAO ID
	VAO() {
		glGenVertexArrays(1, &ID);
	}

	// Links a VBO to the VAO using a certain layout
	void LinkVBO(VBO& VBO, GLuint layout) {
		VBO.Bind();
		glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(layout);
		VBO.Unbind();
	}

	// Binds the VAO
	void Bind() {
		glBindVertexArray(ID);
	}

	// Unbinds the VAO
	void Unbind() {
		glBindVertexArray(0);
	}

	// Deletes the VAO
	void Delete() {
		glDeleteVertexArrays(1, &ID);
	}
};

#endif