#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
	//����shaderProgram����id
public :
	unsigned int id;
	Shader(const char* shaderPath)
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

	/// <summary>
	/// �������
	/// </summary>
	void Use() 
	{
		glUseProgram((id));
	}

	void SetBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
	}

	void SetInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	}

	void SetFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	}

private:
	struct _ShaderProgramSource
	{
		std::string VertexShaderSource;
		std::string FragmentShaderSource;
	};

	/// <summary>
	/// �����ļ��е���ɫ��Դ��
	/// </summary>
	/// <param name="path">��ɫ���ļ�λ��</param>
	/// <returns>��ɫ��Դ��</returns>
	_ShaderProgramSource ParseShader(const char* path)
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

	/// <summary>
	/// ������ɫ��Դ��
	/// </summary>
	/// <param name="shaderType">��ɫ������</param>
	/// <param name="source">��ɫ��Դ��</param>
	/// <returns>��ɫ����id</returns>
	unsigned int _CompileShader(unsigned int shaderType ,std::string source)
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
};
#endif // ! SHADER_H

