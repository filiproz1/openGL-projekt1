//TODO@JA: r e f a k t o r y z a c j a
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<cmath>

#include"ShaderClass.h"
#include"EBO.h"
#include"VAO.h"
#include"VBO.h"
#include"Matrix4f.h"
#include"DiscArrays.h"

constexpr float M_PI = 3.14159;

/* dummy variables----------------------- */
const int number_of_elements = 100;
float circlePosition[2] = { 0.f,0.f };
float circleColor[7][3] = { {1,1,0}, {0.11f, 0.32f, 0.78f}, {0.41f, 0.82f, 0.08f}, {0.2f, 0.33f, 1}, {0.8f, 0.37f, 0.21f}, {0.23f, 0.32f, 0.f}, {0.1f, 0.3f, 0.37f} };

/*----------------------------------------*/

int main()
{
	DiscArrays disc1(number_of_elements);
	disc1.discVertices(0.15f, circlePosition, circleColor[0], number_of_elements);
	disc1.discIndices(number_of_elements);

	DiscArrays disc2(number_of_elements);
	disc2.discVertices(0.03f, circlePosition, circleColor[1], number_of_elements);
	disc2.discIndices(number_of_elements);

	DiscArrays disc3(number_of_elements);
	disc3.discVertices(0.042f, circlePosition, circleColor[2], number_of_elements);
	disc3.discIndices(number_of_elements);

	DiscArrays disc4(number_of_elements);
	disc4.discVertices(0.04f, circlePosition, circleColor[3], number_of_elements);
	disc4.discIndices(number_of_elements);

	DiscArrays disc5(number_of_elements);
	disc5.discVertices(0.035f, circlePosition, circleColor[4], number_of_elements);
	disc5.discIndices(number_of_elements);

	DiscArrays disc6(number_of_elements);
	disc6.discVertices(0.07f, circlePosition, circleColor[5], number_of_elements);
	disc6.discIndices(number_of_elements);

	DiscArrays disc7(number_of_elements);
	disc7.discVertices(0.021f, circlePosition, circleColor[6], number_of_elements);
	disc7.discIndices(number_of_elements);

	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1024, 1024, "Openglwindow", NULL, NULL);
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
	glViewport(0, 0, 1024, 1024);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1, VAO2, VAO3, VAO4, VAO5, VAO6, VAO7;
	VAO1.bind();


	GLint transformationLocation = glGetUniformLocation(shaderProgram.ID, "transformation");

	VBO VBO1(disc1.vertices, disc1.vertices_size);
	EBO EBO1(disc1.indices, disc1.indices_size);
	GLuint elemSize = disc1.indices_length;

	VAO1.LinkVBO(VBO1, 0, 1);

	VAO1.unbind();
	VBO1.unbind();
	EBO1.unbind();

	VAO2.bind();

	VBO VBO2(disc2.vertices, disc2.vertices_size);
	EBO EBO2(disc2.indices, disc2.indices_size);
	GLuint elemSize2 = disc2.indices_length;

	VAO2.LinkVBO(VBO2, 0, 1);

	VAO2.unbind();
	VBO2.unbind();
	EBO2.unbind();

	VAO3.bind();

	VBO VBO3(disc3.vertices, disc3.vertices_size);
	EBO EBO3(disc3.indices, disc3.indices_size);
	GLuint elemSize3 = disc3.indices_length;

	VAO3.LinkVBO(VBO3, 0, 1);

	VAO3.unbind();
	VBO3.unbind();
	EBO3.unbind();

	VAO4.bind();

	VBO VBO4(disc4.vertices, disc4.vertices_size);
	EBO EBO4(disc4.indices, disc4.indices_size);
	GLuint elemSize4 = disc4.indices_length;

	VAO4.LinkVBO(VBO4, 0, 1);

	VAO4.unbind();
	VBO4.unbind();
	EBO4.unbind();

	VAO5.bind();

	VBO VBO5(disc5.vertices, disc5.vertices_size);
	EBO EBO5(disc5.indices, disc5.indices_size);
	GLuint elemSize5 = disc5.indices_length;

	VAO5.LinkVBO(VBO5, 0, 1);

	VAO5.unbind();
	VBO5.unbind();
	EBO5.unbind();

	VAO6.bind();

	VBO VBO6(disc6.vertices, disc6.vertices_size);
	EBO EBO6(disc6.indices, disc6.indices_size);
	GLuint elemSize6 = disc6.indices_length;

	VAO6.LinkVBO(VBO6, 0, 1);

	VAO6.unbind();
	VBO6.unbind();
	EBO6.unbind();

	VAO7.bind();

	VBO VBO7(disc7.vertices, disc7.vertices_size);
	EBO EBO7(disc7.indices, disc7.indices_size);
	GLuint elemSize7 = disc7.indices_length;

	VAO7.LinkVBO(VBO7, 0, 1);

	VAO7.unbind();
	VBO7.unbind();
	EBO7.unbind();

	//TODO: wypierdolic to w pizdu i zrobic petle, w trakcie tworzenia moj mozg zapomnial o istnieniu czegos takiego XD

	float timer = .0f;
	float timer2 = .0f;
	float timer3 = .0f;
	while (!glfwWindowShouldClose(window))
	{
		// Ustaw kolor t³a (RGBA, z przedzia³u <0, 1>)
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Wyczyœæ buffor I nadaj mu kolor
		glClear(GL_COLOR_BUFFER_BIT);
		// Wybierz, który shader bêdzie u¿ywany
		shaderProgram.Activate();



		//argumenty do translacji obiektu
		float translate_x = 0;  
		float translate_y = 0;  

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
		VAO1.unbind();

		float translate_x2 = cosf(2.f * M_PI * timer) / 5.2;  
		float translate_y2 = sinf(2.f * M_PI * timer) / 5.2;  


		Matrix4f translation2(1.f, 0.f, 0.f, translate_x2,
			0.f, 1.f, 0.f, translate_y2,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);
		Matrix4f rotation2(0, -1, 0.f, 0.f,
			1, 0, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);

		Matrix4f m2(translation2, rotation2);
		Matrix4f transformation2(m2, scale);

		glUniformMatrix4fv(transformationLocation, 1, GL_TRUE, &transformation2.m[0][0]);

		VAO2.bind();
		glDrawElements(GL_TRIANGLE_FAN, elemSize2, GL_UNSIGNED_INT, 0);
		VAO2.unbind();

		float translate_x3 = cosf(2.f * M_PI * timer2) / 3.7;  
		float translate_y3 = sinf(2.f * M_PI * timer2) / 3.7;  


		Matrix4f translation3(1.f, 0.f, 0.f, translate_x3,
			0.f, 1.f, 0.f, translate_y3,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);
		Matrix4f rotation3(cosf(angle_of_rotation), -sinf(angle_of_rotation), 0.f, 0.f,
			sinf(angle_of_rotation), cosf(angle_of_rotation), 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);

		Matrix4f m3(translation3, rotation3);
		Matrix4f transformation3(m3, scale);

		glUniformMatrix4fv(transformationLocation, 1, GL_TRUE, &transformation3.m[0][0]);

		VAO3.bind();
		glDrawElements(GL_TRIANGLE_FAN, elemSize3, GL_UNSIGNED_INT, 0);
		VAO3.unbind();

		float translate_x4 = cosf(2.f * M_PI * (timer2 + timer)) / 3.7;  
		float translate_y4 = sinf(2.f * M_PI * (timer2 + timer)) / 3.7; 

		Matrix4f translation4(1.f, 0.f, 0.f, translate_x4*1.3,
			0.f, 1.f, 0.f, translate_y4*1.3,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);
		Matrix4f rotation4(cosf(angle_of_rotation), -sinf(angle_of_rotation), 0.f, 0.f,
			sinf(angle_of_rotation), cosf(angle_of_rotation), 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);

		Matrix4f m4(translation4, rotation4);
		Matrix4f transformation4(m4, scale);

		glUniformMatrix4fv(transformationLocation, 1, GL_TRUE, &transformation4.m[0][0]);

		VAO4.bind();
		glDrawElements(GL_TRIANGLE_FAN, elemSize4, GL_UNSIGNED_INT, 0);
		VAO4.unbind();

		float translate_x5 = cosf(2.f * M_PI * (timer - timer2)) / 3.7;  
		float translate_y5 = sinf(2.f * M_PI * (timer - timer2)) / 3.7;  


		Matrix4f translation5(1.f, 0.f, 0.f, translate_x5 * 1.8,
			0.f, 1.f, 0.f, translate_y5 * 1.8,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);
		Matrix4f rotation5(cosf(angle_of_rotation), -sinf(angle_of_rotation), 0.f, 0.f,
			sinf(angle_of_rotation), cosf(angle_of_rotation), 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);

		Matrix4f m5(translation5, rotation5);
		Matrix4f transformation5(m5, scale);

		glUniformMatrix4fv(transformationLocation, 1, GL_TRUE, &transformation5.m[0][0]);

		VAO5.bind();
		glDrawElements(GL_TRIANGLE_FAN, elemSize5, GL_UNSIGNED_INT, 0);
		VAO5.unbind();

		float translate_x6 = cosf(2.f * M_PI * timer3) / 3.7;  
		float translate_y6 = sinf(2.f * M_PI * timer3) / 3.7;  

		Matrix4f translation6(1.f, 0.f, 0.f, translate_x6 * 2.3,
			0.f, 1.f, 0.f, translate_y6 * 2.3,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);
		Matrix4f rotation6(cosf(angle_of_rotation), -sinf(angle_of_rotation), 0.f, 0.f,
			sinf(angle_of_rotation), cosf(angle_of_rotation), 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);

		Matrix4f m6(translation6, rotation6);
		Matrix4f transformation6(m6, scale);

		glUniformMatrix4fv(transformationLocation, 1, GL_TRUE, &transformation6.m[0][0]);

		VAO6.bind();
		glDrawElements(GL_TRIANGLE_FAN, elemSize6, GL_UNSIGNED_INT, 0);
		VAO6.unbind();

		float translate_x7 = cosf(2.f * M_PI * (timer3 - timer2)) / 3.7;  
		float translate_y7 = sinf(2.f * M_PI * (timer3 - timer2)) / 3.7;  

		Matrix4f translation7(1.f, 0.f, 0.f, translate_x7 * 2.8,
			0.f, 1.f, 0.f, translate_y7 * 2.8,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);
		Matrix4f rotation7(cosf(angle_of_rotation), -sinf(angle_of_rotation), 0.f, 0.f,
			sinf(angle_of_rotation), cosf(angle_of_rotation), 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);

		Matrix4f m7(translation7, rotation7);
		Matrix4f transformation7(m7, scale);

		glUniformMatrix4fv(transformationLocation, 1, GL_TRUE, &transformation7.m[0][0]);

		VAO7.bind();
		glDrawElements(GL_TRIANGLE_FAN, elemSize7, GL_UNSIGNED_INT, 0);
		VAO7.unbind();
		


		// Odœwie¿ widok
		glfwSwapBuffers(window);
		glfwWaitEventsTimeout(1./ 60.);
		timer = (timer > 1.0f) ? .0f : timer + 0.01f;
		timer2 = (timer2 > 2.0f) ? .0f : timer2 + 0.013f;
		timer3 = (timer3 > 1.0f) ? .0f : timer3 + 0.015f;
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