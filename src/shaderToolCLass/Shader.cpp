#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

Shader::Shader(const char* shaderPath)
{
	_ShaderProgramSource shaderSource = ParseShader(shaderPath);

	unsigned int vertexShader = _CompileShader(GL_VERTEX_SHADER, shaderSource.VertexShaderSource);
	unsigned int fragmentShader = _CompileShader(GL_FRAGMENT_SHADER, shaderSource.FragmentShaderSource);
	unsigned int program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	id = program;
}

void Shader::Use()
{
	glUseProgram(id);
}

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::SetMat4f(const std::string& name, glm::mat4& mat4) const
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat4[0][0]);
}

Shader::_ShaderProgramSource Shader::ParseShader(const char* path)
{
	std::ifstream stream(path);
	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1,
	};
	std::stringstream ss[2];

	ShaderType type = ShaderType::NONE;
	std::string line;
	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			if (type != ShaderType::NONE)
			{
				ss[(int)type] << line << "\n";
			}
		}
	}
	std::cout << "-------------READ SHADERSOURCE------------" << std::endl;
	std::cout << "The VertexShader Source : " << std::endl;
	std::cout << ss[0].str() << std::endl;

	std::cout << "The FragmentShader Source : " << std::endl;
	std::cout << ss[1].str() << std::endl;
	std::cout << "------------------------------" << std::endl;

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::_CompileShader(unsigned int shaderType, std::string source)
{
	unsigned int id = glCreateShader(shaderType);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		int lenth;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenth);
		char* message = (char*)_malloca(lenth * sizeof(char));
		glGetShaderInfoLog(id, lenth, &lenth, message);
		std::cout << "-------------ERROR------------" << std::endl;
		std::cout << "Fail to compile shader : " << std::endl;
		std::cout << message << std::endl;
		std::cout << "------------------------------" << std::endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
}