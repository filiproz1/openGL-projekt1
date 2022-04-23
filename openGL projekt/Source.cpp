#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<cmath>

#include"ShaderClass.h"
#include"EBO.h"
#include"VAO.h"
#include"VBO.h"
#include"Matrix4f.h"

constexpr float M_PI = 3.14159;

const int number_of_elements = 100;

GLfloat* circleVertices(float radius, float pos[2], float color[3], int number_of_elements)
{
	int size = 5 * (number_of_elements + 1);
	GLfloat* result = new GLfloat[size];

	//punkt œrodka ko³a - wspó³rzêdne i kolor
	result[0] = pos[0];
	result[1] = pos[1];
	result[2] = color[0];
	result[3] = color[1];
	result[4] = color[2];

	for (int i = 1; i < size / 5; i++)
	{
		float angle = 2.0f * M_PI  * float(i) / float(number_of_elements-1);
		float dx = radius * cosf(angle);
		float dy = radius * sinf(angle);
		result[5 * i] =		pos[0] + dx;
		result[5 * i + 1] = pos[1] + dy;
		result[5 * i + 2] = color[0];
		result[5 * i + 3] = color[1];
		result[5 * i + 4] = color[2];
	}
	return result;
}

GLuint* circleIndices(int number_of_elements)
{
	int size = number_of_elements+1;
	GLuint* result = new GLuint[size];
	for (int i = 0; i < size; i++)
	{
		result[i] = i;
	}
	return result;
}

float circlePosition[2] = { .2f,0 };
float circleColor[3] = { 1,0,0 };
GLfloat* vertices2 = circleVertices(0.2f, circlePosition, circleColor, number_of_elements);
int size_of_vertices = (5 * number_of_elements + 5)*sizeof(GLfloat);
GLuint* indices2 = circleIndices(number_of_elements);
int size_of_indices = (number_of_elements + 1) * sizeof(GLuint);

int main()
{
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Openglwindow", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.bind();


	GLint transformationLocation = glGetUniformLocation(shaderProgram.ID, "transformation");

	VBO VBO1(vertices2, size_of_vertices);
	EBO EBO1(indices2, size_of_indices);
	GLuint elemSize = size_of_indices/sizeof(GLuint);

	VAO1.LinkVBO(VBO1, 0, 1);

	VAO1.unbind();
	VBO1.unbind();
	EBO1.unbind();
	float timer = .0f;
	while (!glfwWindowShouldClose(window))
	{
		// Ustaw kolor t³a (RGBA, z przedzia³u <0, 1>)
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Wyczyœæ buffor I nadaj mu kolor
		glClear(GL_COLOR_BUFFER_BIT);
		// Wybierz, który shader bêdzie u¿ywany
		shaderProgram.Activate();

		//argumenty do translacji obiektu
		float translate_x = cosf(2.f * M_PI * timer)/5;
		float translate_y = sinf(2.f * M_PI * timer)/5;

		//argumenty do rotacji obiektu
		float angle_of_rotation = 0.f;

		//argumenty do skalowania obiektu
		float scale_x = 0.f;
		float scale_y = 0.f;

		//macierze translacji, rotacji i skalowania
		Matrix4f translation(1.f, 0.f, 0.f, translate_x,
						 	 0.f, 1.f, 0.f, translate_y,
							 0.f, 0.f, 1.f, 0.f,
							 0.f, 0.f, 0.f, 1.f);
		Matrix4f rotation(cosf(angle_of_rotation),	-sinf(angle_of_rotation),	0.f, 0.f,
						  sinf(angle_of_rotation),	cosf(angle_of_rotation),	0.f, 0.f,
						  0.f,						0.f,						1.f, 0.f,
						  0.f,						0.f,						0.f, 1.f);
		Matrix4f scale(	1.f + scale_x,	0.f,			0.f, 0.f,
						0.f,			1.f + scale_y,	0.f, 0.f,
						0.f,			0.f,			1.f, 0.f,
						0.f,			0.f,			0.f, 1.f);

		//mnozenie macierzy aby uzyskac jedna macierz transformacji
		Matrix4f m1(translation, rotation);
		Matrix4f transformation(m1, scale);

		glUniformMatrix4fv(transformationLocation, 1, GL_TRUE, &transformation.m[0][0]);

		VAO1.bind();
		// Narysuj trójk¹t
		glDrawElements(GL_TRIANGLE_FAN, elemSize, GL_UNSIGNED_INT, 0);
		// Odœwie¿ widok
		glfwSwapBuffers(window);
		glfwWaitEventsTimeout(1./ 60.);
		timer = (timer > 1.0f) ? .0f : timer + 0.01f;
	}


	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}