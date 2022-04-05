#ifndef SHADER_H
#define SHADER_H

#include <string>
#include "../../Dependencies/glm/glm.hpp"
#include <unordered_map>

class Shader {
	//程序（shaderProgram）的id
private:
	unsigned int m_id;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public :
	
	Shader(const char* shaderPath);

	void Bind() const;

	void UnBind() const;

	void SetBool(const std::string& name, bool value);

	void SetInt(const std::string& name, int value) ;

	void SetFloat(const std::string& name, float value);

	void SetVec3(const std::string& name, const glm::vec3& vec3);

	void SetMat4f(const std::string& name, const glm::mat4& mat4);
	 
private:
	struct _ShaderProgramSource
	{
		std::string VertexShaderSource;
		std::string FragmentShaderSource;
		std::string GeometryShaderSource;
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

	/// <summary>
	/// 
	/// </summary>
	int GetUniformLocation(const std::string& name);
};
#endif // ! SHADER_H

