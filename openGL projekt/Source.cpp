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
float circleColor[9][3] = { {1,1,0}, {0.11f, 0.32f, 0.78f}, {0.41f, 0.82f, 0.08f}, {0.2f, 0.33f, 1}, {0.8f, 0.37f, 0.21f}, {0.23f, 0.32f, 0.f}, {0.1f, 0.3f, 0.37f}, {0.21f, 0.3f, 0.7f}, {0.3f, 0.3f, 0.f} };
float circleRandius[9] = { 0.15f, 0.03f, 0.042f, 0.04f, 0.035f, 0.07f, 0.021f, 0.026f, 0.019f};

/*----------------------------------------*/

int main()
{
	DiscArrays disc[9];

	for (int i = 0; i < 9; i++) 
	{
		disc[i].init(number_of_elements);
		disc[i].discVertices(circleRandius[i], circlePosition, circleColor[i], number_of_elements);
		disc[i].discIndices(number_of_elements);
	}

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

	VAO arrVAO[9];
	VBO arrVBO[9];
	EBO arrEBO[9];
	GLuint elemSz[9];

	for (int i = 0; i < 9; i++) {
		arrVAO[i].bind();
		arrVBO[i].init(disc[i].vertices, disc[i].vertices_size);
		arrEBO[i].init(disc[i].indices, disc[i].indices_size);
		elemSz[i] = disc[i].indices_length;

		arrVAO[i].LinkVBO(arrVBO[i], 0, 1);
		arrVAO[i].unbind();
		arrVBO[i].unbind();
		arrEBO[i].unbind();
	}

	GLint transformationLocation = glGetUniformLocation(shaderProgram.ID, "transformation");

	float timer(0.0), timer2(0.0), timer3(0.0), timer4(0.0), timer5(0.0), timer6(0.0), timer7(0.0), timer8(0.0);

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

		arrVAO[0].bind();
		// Narysuj trójk¹t
		glDrawElements(GL_TRIANGLE_FAN, elemSz[0], GL_UNSIGNED_INT, 0);
		arrVAO[0].unbind();

		float translate_x2 = cosf(2.f * M_PI * timer) / 5.2;  
		float translate_y2 = sinf(2.f * M_PI * timer) / 5.2;  


		Matrix4f translation2(1.f, 0.f, 0.f, translate_x2,
			0.f, 1.f, 0.f, translate_y2,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);

		Matrix4f m2(translation2, rotation);
		Matrix4f transformation2(m2, scale);

		glUniformMatrix4fv(transformationLocation, 1, GL_TRUE, &transformation2.m[0][0]);

		arrVAO[1].bind();
		glDrawElements(GL_TRIANGLE_FAN, elemSz[1], GL_UNSIGNED_INT, 0);
		arrVAO[1].unbind();

		float translate_x3 = cosf(2.f * M_PI * timer2) / 3.7;  
		float translate_y3 = sinf(2.f * M_PI * timer2) / 3.7;  


		Matrix4f translation3(1.f, 0.f, 0.f, translate_x3,
			0.f, 1.f, 0.f, translate_y3,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);

		Matrix4f m3(translation3, rotation);
		Matrix4f transformation3(m3, scale);

		glUniformMatrix4fv(transformationLocation, 1, GL_TRUE, &transformation3.m[0][0]);

		arrVAO[2].bind();
		glDrawElements(GL_TRIANGLE_FAN, elemSz[2], GL_UNSIGNED_INT, 0);
		arrVAO[2].unbind();

		float translate_x4 = cosf(2.f * M_PI * timer3) / 3.7;  
		float translate_y4 = sinf(2.f * M_PI * timer3) / 3.7; 

		Matrix4f translation4(1.f, 0.f, 0.f, translate_x4*1.3,
			0.f, 1.f, 0.f, translate_y4*1.3,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);

		Matrix4f m4(translation4, rotation);
		Matrix4f transformation4(m4, scale);

		glUniformMatrix4fv(transformationLocation, 1, GL_TRUE, &transformation4.m[0][0]);

		arrVAO[3].bind();
		glDrawElements(GL_TRIANGLE_FAN, elemSz[3], GL_UNSIGNED_INT, 0);
		arrVAO[3].unbind();

		float translate_x5 = cosf(2.f * M_PI * timer4) / 3.7;  
		float translate_y5 = sinf(2.f * M_PI * timer4) / 3.7;  


		Matrix4f translation5(1.f, 0.f, 0.f, translate_x5 * 1.8,
			0.f, 1.f, 0.f, translate_y5 * 1.8,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);

		Matrix4f m5(translation5, rotation);
		Matrix4f transformation5(m5, scale);

		glUniformMatrix4fv(transformationLocation, 1, GL_TRUE, &transformation5.m[0][0]);

		arrVAO[4].bind();
		glDrawElements(GL_TRIANGLE_FAN, elemSz[4], GL_UNSIGNED_INT, 0);
		arrVAO[4].unbind();

		float translate_x6 = cosf(2.f * M_PI * timer5) / 3.7;  
		float translate_y6 = sinf(2.f * M_PI * timer5) / 3.7;  

		Matrix4f translation6(1.f, 0.f, 0.f, translate_x6 * 2.3,
			0.f, 1.f, 0.f, translate_y6 * 2.3,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);

		Matrix4f m6(translation6, rotation);
		Matrix4f transformation6(m6, scale);

		glUniformMatrix4fv(transformationLocation, 1, GL_TRUE, &transformation6.m[0][0]);

		arrVAO[5].bind();
		glDrawElements(GL_TRIANGLE_FAN, elemSz[5], GL_UNSIGNED_INT, 0);
		arrVAO[5].unbind();

		float translate_x7 = cosf(2.f * M_PI * timer6) / 3.7;  
		float translate_y7 = sinf(2.f * M_PI * timer6) / 3.7;  

		Matrix4f translation7(1.f, 0.f, 0.f, translate_x7 * 2.8,
			0.f, 1.f, 0.f, translate_y7 * 2.8,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);

		Matrix4f m7(translation7, rotation);
		Matrix4f transformation7(m7, scale);

		glUniformMatrix4fv(transformationLocation, 1, GL_TRUE, &transformation7.m[0][0]);

		arrVAO[6].bind();
		glDrawElements(GL_TRIANGLE_FAN, elemSz[6], GL_UNSIGNED_INT, 0);
		arrVAO[6].unbind();

		float translate_x8 = cosf(2.f * M_PI * timer7) / 3.7;
		float translate_y8 = sinf(2.f * M_PI * timer7) / 3.7;

		Matrix4f translation8(1.f, 0.f, 0.f, translate_x8 * 3,
			0.f, 1.f, 0.f, translate_y8 * 3,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);

		Matrix4f m8(translation8, rotation);
		Matrix4f transformation8(m8, scale);

		glUniformMatrix4fv(transformationLocation, 1, GL_TRUE, &transformation8.m[0][0]);

		arrVAO[7].bind();
		glDrawElements(GL_TRIANGLE_FAN, elemSz[7], GL_UNSIGNED_INT, 0);
		arrVAO[7].unbind();

		float translate_x9 = cosf(2.f * M_PI * timer8) / 3.7;
		float translate_y9 = sinf(2.f * M_PI * timer8) / 3.7;

		Matrix4f translation9(1.f, 0.f, 0.f, translate_x9 * 3.3,
			0.f, 1.f, 0.f, translate_y9 * 3.3,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);

		Matrix4f m9(translation9, rotation);
		Matrix4f transformation9(m9, scale);

		glUniformMatrix4fv(transformationLocation, 1, GL_TRUE, &transformation9.m[0][0]);

		arrVAO[8].bind();
		glDrawElements(GL_TRIANGLE_FAN, elemSz[8], GL_UNSIGNED_INT, 0);
		arrVAO[8].unbind();



		// Odœwie¿ widok
		glfwSwapBuffers(window);
		glfwWaitEventsTimeout(1./ 60.);
		timer = (timer > 1.0f) ? .0f : timer + 0.01f;
		timer2 = (timer2 > 2.0f) ? .0f : timer2 + 0.013f;
		timer3 = (timer3 > 1.0f) ? .0f : timer3 + 0.015f;
		timer4 = (timer4 > 2.5f) ? .0f : timer4 + 0.04f;
		timer5 = (timer5 > 1.0f) ? .0f : timer5 + 0.023f;
		timer6 = (timer6 > 1.0f) ? .0f : timer6 + 0.005f;
		timer7 = (timer7 > 1.0f) ? .0f : timer7 + 0.01f;
		timer8 = (timer8 > 2.0f) ? .0f : timer8 + 0.01f;
	}

	for (int i = 0; i < 9; i++)
	{
		arrVAO[i].Delete();
		arrVBO[i].Delete();
		arrEBO[i].Delete();
	}
	///VAO1.Delete();
	///VBO1.Delete();
	///EBO1.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}