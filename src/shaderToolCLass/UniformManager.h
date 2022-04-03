#pragma once
#include <string>
#include <unordered_map>
#include "shader.h"
#include <vector>
enum class UniformType
{
	INT,
	FLOAT,
	BOOL,
	VEC3,
	MAT4,
};

struct  Uniform
{	
	UniformType type;
	const void* data;
};

class UniformManager
{
private:
	std::unordered_map<std::string, Uniform> m_uniforms;
	void SetData(Shader& shader, Uniform& uniform, std::string name);
public:
	void Push(std::string name, Uniform uniform);
	void SetUniform(Shader& shader, std::string name);
	void SetUniforms(Shader& shader, std::vector<std::string>& names);
};