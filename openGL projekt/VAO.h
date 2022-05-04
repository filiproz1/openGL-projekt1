#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	GLuint ID;
	VAO();

	void bind();
	void unbind();
	void Delete();
	void LinkVBO(VBO& VBO, GLuint position_location, GLuint color_location);


};


#endif
