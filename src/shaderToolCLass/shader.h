#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader {
	//����shaderProgram����id
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
};
#endif // ! SHADER_H

