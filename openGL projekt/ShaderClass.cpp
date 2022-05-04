#include"ShaderClass.h"

std::string getFileContents(const char* path)
{
	std::ifstream in(path, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());

		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	throw(errno);
}

Shader::Shader(const char* vertex_file, const char* fragment_file)
{
	std::string vertex_code = getFileContents(vertex_file);
	std::string fragment_code = getFileContents(fragment_file);

	const char* vertex_source = vertex_code.c_str();
	const char* fragment_source = fragment_code.c_str();

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_source, NULL);
	glCompileShader(vertex_shader);

	compileErrors(vertex_shader, "VERTEX", vertex_source);

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_source, NULL);
	glCompileShader(fragment_shader);

	compileErrors(fragment_shader, "FRAGMENT", fragment_source);

	ID = glCreateProgram();

	glAttachShader(ID, vertex_shader);
	glAttachShader(ID, fragment_shader);
	glLinkProgram(ID);

	compileErrors(ID, "PROGRAM", vertex_source + (std::string)"\n" + fragment_source);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type, std::string shaderCode)
{
	char infoLog[1024];
	GLint hasCompiled;

	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		std::cout << type << " SHADER -> STATUS KOMPILACJI: ";
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) glGetProgramInfoLog(shader, 1024, NULL, infoLog);
		std::cout << type << " STATUS LINKOWANIA: ";
	}
	if (hasCompiled == GL_TRUE) std::cout << "gituwa\n";
	else
	{
		std::cout << "niegituwa\n";
		std::cout << shaderCode << "\n";
	}
}