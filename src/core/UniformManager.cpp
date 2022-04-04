#include "UniformManager.h"
void UniformManager::Push(std::string name ,Uniform uniform)
{
	if (m_uniforms.count(name) == 0)
	{
		m_uniforms[name] = uniform;
	}
}

void UniformManager::SetUniform(Shader& shader, std::string name)
{
	shader.Bind();
	SetData(shader, m_uniforms[name], name);
	shader.UnBind();
}

void UniformManager::SetUniforms(Shader& shader, std::vector<std::string>& names)
{
	shader.Bind();
	for (std::string& name : names)
	{
		SetData(shader, m_uniforms[name], name);
	}
	shader.UnBind();
}

void UniformManager::SetData(Shader& shader, Uniform& uniform, std::string name)
{
	switch (uniform.type)
	{
	case UniformType::INT:
		shader.SetInt(name, *(int*)uniform.data);
		break;
	case UniformType::BOOL:
		shader.SetBool(name, *(bool*)uniform.data);
		break;
	case UniformType::FLOAT:
		shader.SetFloat(name, *(float*)uniform.data);
		break;
	case UniformType::VEC3:
		shader.SetVec3(name, *(glm::vec3*)uniform.data);
		break;
	case UniformType::MAT4:
		shader.SetMat4f(name, *(glm::mat4*)uniform.data);
		break;
	}
}