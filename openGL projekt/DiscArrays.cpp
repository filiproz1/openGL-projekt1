#include"DiscArrays.h"
#include<cmath>

constexpr float M_PI = 3.14159;


DiscArrays::DiscArrays(int number_of_elements)
{
	indices_length = number_of_elements + 1;
	indices_size = indices_length * sizeof(GLuint);
	indices = new GLuint[indices_length];

	vertices_length = 5 * (number_of_elements + 1);
	vertices_size = vertices_length * sizeof(GLfloat);
	vertices = new GLfloat[vertices_length];

}

DiscArrays::DiscArrays()
{

}

void DiscArrays::init(int number_of_elements)
{
	indices_length = number_of_elements + 1;
	indices_size = indices_length * sizeof(GLuint);
	indices = new GLuint[indices_length];

	vertices_length = 5 * (number_of_elements + 1);
	vertices_size = vertices_length * sizeof(GLfloat);
	vertices = new GLfloat[vertices_length];
}

void DiscArrays::discIndices(int number_of_elements)
{
	for (int i = 0; i < indices_length; i++)
	{
		indices[i] = i;
	}
}

void DiscArrays::discVertices(float radius, float pos[2], float color[3], int number_of_elements)
{

	for (int i = 0; i < vertices_length / 5; i++)
	{
		float angle = 2.0f * M_PI * float(i) / float(number_of_elements - 1);
		float dx = radius * cosf(angle);
		float dy = radius * sinf(angle);
		vertices[5 * i] = pos[0] + dx;
		vertices[5 * i + 1] = pos[1] + dy;
		vertices[5 * i + 2] = color[0];
		vertices[5 * i + 3] = color[1];
		vertices[5 * i + 4] = color[2];
	}
}