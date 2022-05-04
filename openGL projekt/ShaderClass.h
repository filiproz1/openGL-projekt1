#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>
#include<fstream>
#include<sstream>
#include<cerrno>


std::string getFileContents(const char* path);

class Shader
{
public:
	GLuint ID;
	Shader(const char* vertex_file, const char* fragment_file);

	void Activate();
	void Delete();

private:
	void compileErrors(unsigned int shader, const char* type, std::string shaderCode);
};

#endif
