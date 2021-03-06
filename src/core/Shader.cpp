#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include "Renderer.h"

Shader::Shader(const char* shaderPath)
{
	_ShaderProgramSource shaderSource = ParseShader(shaderPath);

	unsigned int vertexShader = _CompileShader(GL_VERTEX_SHADER, shaderSource.VertexShaderSource);
	unsigned int fragmentShader = _CompileShader(GL_FRAGMENT_SHADER, shaderSource.FragmentShaderSource);
	unsigned int geometryShader = 0;
	if(shaderSource.GeometryShaderSource.size() != 0)
		geometryShader = _CompileShader(GL_GEOMETRY_SHADER, shaderSource.GeometryShaderSource);
	unsigned int program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	if (geometryShader != 0)
		glAttachShader(program, geometryShader);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geometryShader != 0)
		glDeleteShader(geometryShader);

	m_id = program;
}

void Shader::Bind() const
{
	glUseProgram(m_id);
}

void Shader::UnBind() const
{
	glUseProgram(0);
}

void Shader::SetBool(const std::string& name, bool value)
{
	glUniform1i(GetUniformLocation(name), (int)value);
}

void Shader::SetInt(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetFloat(const std::string& name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& vec3)
{
	glUniform3f(GetUniformLocation(name), vec3.x, vec3.y, vec3.z);
}

void Shader::SetMat4f(const std::string& name,const glm::mat4& mat4) 
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat4[0][0]);
}


int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_id, name.c_str()));
	if (location == -1)
		std::cout << "[Warning] : Didn't find uniform named " << name << std::endl;

	m_UniformLocationCache[name] = location;

	return location;
}

Shader::_ShaderProgramSource Shader::ParseShader(const char* path)
{
	std::ifstream stream(path);
	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2
	};
	std::stringstream ss[3];

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
			else if (line.find("geometry") != std::string::npos)
				type = ShaderType::GEOMETRY;
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

	std::cout << "The Geometry Source : " << std::endl;
	std::cout << ss[2].str() << std::endl;
	std::cout << "-------------------------------------------" << std::endl;

	return { ss[0].str(), ss[1].str(), ss[2].str() };
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