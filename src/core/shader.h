#ifndef SHADER_H
#define SHADER_H

#include <string>
#include "../../Dependencies/glm/glm.hpp"
#include <unordered_map>

class Shader {
	//����shaderProgram����id
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
	/// �����ļ��е���ɫ��Դ��
	/// </summary>
	/// <param name="path">��ɫ���ļ�λ��</param>
	/// <returns>��ɫ��Դ��</returns>
	_ShaderProgramSource ParseShader(const char* path);

	/// <summary>
	/// ������ɫ��Դ��
	/// </summary>
	/// <param name="shaderType">��ɫ������</param>
	/// <param name="source">��ɫ��Դ��</param>
	/// <returns>��ɫ����id</returns>
	unsigned int _CompileShader(unsigned int shaderType, std::string source);

	/// <summary>
	/// 
	/// </summary>
	int GetUniformLocation(const std::string& name);
};
#endif // ! SHADER_H

