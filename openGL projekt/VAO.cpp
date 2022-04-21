#include"VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

void VAO::bind()
{
	glBindVertexArray(ID);
}

void VAO::unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}

void VAO::LinkVBO(VBO& VBO, GLuint position_location, GLuint color_location)
{
	glEnableVertexAttribArray(position_location);

	glVertexAttribPointer(position_location, 2, GL_FLOAT, GL_FALSE, 
		5 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(color_location);

	glVertexAttribPointer(color_location, 3, GL_FLOAT, GL_FALSE, 
		5 * sizeof(float), (void*)(2*sizeof(float)));

	VBO.unbind();
}