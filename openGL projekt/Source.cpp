#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<cmath>

#include"ShaderClass.h"
#include"EBO.h"
#include"VAO.h"
#include"VBO.h"

class Matrix4f
{
public:
	float m[4][4] = { {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} };

	Matrix4f() {};
	Matrix4f(float a00, float a01, float a02, float a03,
			 float a10, float a11, float a12, float a13,
			 float a20, float a21, float a22, float a23,
		 	 float a30, float a31, float a32, float a33)
	{
		m[0][0] = a00; m[0][1] = a01; m[0][2] = a02; m[0][3] = a03;
		m[1][0] = a10; m[1][1] = a11; m[1][2] = a12; m[1][3] = a13;
		m[2][0] = a20; m[2][1] = a21; m[2][2] = a22; m[2][3] = a23;
		m[3][0] = a30; m[3][1] = a31; m[3][2] = a32; m[3][3] = a33;
	}

	Matrix4f(Matrix4f m1, Matrix4f m2)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					m[i][j] += m1.m[i][k] * m2.m[k][j];
				}
			}
		}
	}
};

GLfloat vertices[] =
{
	-0.1,	0.1,	1.0,	0.0,	0.0,
	0.1,	0.1,	0.0,	1.0,	0.0,
	0.1,	-0.1,	0.0,	0.0,	1.0,
	-0.1,	-0.1,	0.0,	1.0,	0.0
};

GLuint indices[] =
{
	0,1,2,
	2,3,0
};

GLfloat* circleVertices(float radius, float pos[2], float color[3], int number_of_elements = 360)
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
		float angle = 2.0f * 3.1415926f * i / number_of_elements;
		result[5 * i] =		pos[0] + radius * cosf(angle);
		result[5 * i + 1] = pos[1] + radius * sinf(angle);
		result[5 * i + 2] = color[0];
		result[5 * i + 3] = color[1];
		result[5 * i + 4] = color[2];
	}
	return result;
}

GLuint* circleIndices(int number_of_elements)
{
	int size = 3 * number_of_elements;
	GLuint* result = new GLuint[size];
	return result;
}

float circlePosition[2] = { 0,0 };
float circleColor[3] = { 1,0,0 };
GLfloat* vertices2 = circleVertices(1.0f, circlePosition, circleColor);
int size_of_vertices = (5 * 360 + 5)/sizeof(GLfloat);

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

	//GLint translationLocation = glGetUniformLocation(shaderProgram.ID, "translation");
	//GLint rotationLocation = glGetUniformLocation(shaderProgram.ID, "rotation");
	//GLint scaleLocation = glGetUniformLocation(shaderProgram.ID, "scale");

	GLint transformationLocation = glGetUniformLocation(shaderProgram.ID, "transformation");

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0, 1);

	VAO1.unbind();
	VBO1.unbind();
	EBO1.unbind();
	float timer = .0f;
	GLuint elemSize = sizeof(indices) / sizeof(GLuint);
	while (!glfwWindowShouldClose(window))
	{
		// Ustaw kolor t³a (RGBA, z przedzia³u <0, 1>)
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Wyczyœæ buffor I nadaj mu kolor
		glClear(GL_COLOR_BUFFER_BIT);
		// Wybierz, który shader bêdzie u¿ywany
		shaderProgram.Activate();

		//argumenty do translacji obiektu
		float translate_x = 0.f;
		float translate_y = 0.f;

		//argumenty do rotacji obiektu
		float angle_of_rotation = 2.0f * 3.14f * timer;

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
		glDrawElements(GL_TRIANGLES, elemSize, GL_UNSIGNED_INT, 0);
		// Odœwie¿ widok
		glfwSwapBuffers(window);
		glfwWaitEventsTimeout(1./ 30.);
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