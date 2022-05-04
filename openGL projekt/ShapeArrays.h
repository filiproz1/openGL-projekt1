#include<glad/glad.h>

class DiscArrays
{
public:
	GLuint* indices;
	GLfloat* vertices;
	int indices_size{};
	int vertices_size{};
	int indices_length{};
	int vertices_length{};

	DiscArrays();
	DiscArrays(int number_of_elements);
	void discVertices(float radius, float pos[2], float color[3], int number_of_elements);
	void discIndices(int number_of_elements);
};