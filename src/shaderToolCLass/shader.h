#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader {
	//程序（shaderProgram）的id
public :
	unsigned int id;
	Shader(const char* shaderPath);

	void Use();

	void SetBool(const std::string& name, bool value) const;

	void SetInt(const std::string& name, int value) const;

	void SetFloat(const std::string& name, float value) const;

private:
	struct _ShaderProgramSource
	{
		std::string VertexShaderSource;
		std::string FragmentShaderSource;
	};

	/// <summary>
	/// 读入文件中的着色器源码
	/// </summary>
	/// <param name="path">着色器文件位置</param>
	/// <returns>着色器源码</returns>
	_ShaderProgramSource ParseShader(const char* path);
	/// <summary>
	/// 编译着色器源码
	/// </summary>
	/// <param name="shaderType">着色器种类</param>
	/// <param name="source">着色器源码</param>
	/// <returns>着色器的id</returns>
	unsigned int _CompileShader(unsigned int shaderType, std::string source);
};
#endif // ! SHADER_H

