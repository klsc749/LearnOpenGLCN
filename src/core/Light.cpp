#include "Light.h"

void LightModel::AddMaterial(const Texture& diffuse, const Texture& specular, const float& shininess)
{
	material.diffuse = diffuse.GetTextureID();
	material.specular = specular.GetTextureID();
	material.shininess = shininess;
}

void LightModel::AddDirLight(const glm::vec3& direction)
{
	dirLight.direction = direction;
}

void LightModel::AddDirLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
{
	dirLight.direction = direction;
	dirLight.ambient = ambient;
	dirLight.diffuse = diffuse;
	dirLight.specular = specular;
}

void LightModel::AddPointLight(const glm::vec3& position)
{
	pointLight.position = position;
}

void LightModel::AddPointLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
{
	pointLight.position = position;
	pointLight.ambient = ambient;
	pointLight.diffuse = diffuse;
	pointLight.specular = specular;
}

void LightModel::AddPointLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
	const float& constant, const float& linear, const float& quadratic)
{
	pointLight.position = position;
	pointLight.ambient = ambient;
	pointLight.diffuse = diffuse;
	pointLight.specular = specular;
	pointLight.constant = constant;
	pointLight.linear = linear;
	pointLight.quadratic = quadratic;
}

void LightModel::AddSpotLight(const glm::vec3& position, const glm::vec3 direction)
{
	spotLight.position = position;
	spotLight.direction = direction;
}

void LightModel::AddSpotLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
	const glm::vec3 direction)
{
	spotLight.position = position;
	spotLight.direction = direction;
	spotLight.ambient = ambient;
	spotLight.diffuse = diffuse;
	spotLight.specular = specular;
}

void LightModel::AddSpotLight(const glm::vec3& position, const glm::vec3 direction,
	const float& constant, const float& linear, const float& quadratic)
{
	spotLight.position = position;
	spotLight.direction = direction;
	spotLight.constant = constant;
	spotLight.linear = linear;
	spotLight.quadratic = quadratic;
}

void LightModel::AddSpotLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
	const glm::vec3 direction,
	const float& constant, const float& linear, const float& quadratic)
{
	spotLight.position = position;
	spotLight.direction = direction;
	spotLight.ambient = ambient;
	spotLight.diffuse = diffuse;
	spotLight.specular = specular;
	spotLight.constant = constant;
	spotLight.linear = linear;
	spotLight.quadratic = quadratic;
}

void LightModel::AddSpotLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
	const glm::vec3 direction,
	const float& constant, const float& linear, const float& quadratic,
	const float& cutOff, const float& outerCutOff)
{
	spotLight.position = position;
	spotLight.direction = direction;
	spotLight.ambient = ambient;
	spotLight.diffuse = diffuse;
	spotLight.specular = specular;
	spotLight.constant = constant;
	spotLight.linear = linear;
	spotLight.quadratic = quadratic;
	spotLight.cutOff = cutOff;
	spotLight.outerCutOff = outerCutOff;
}

void LightModel::SetDirLight(Shader& shader, const std::string& name)
{
	shader.Bind();
	shader.SetVec3(name + ".direction", dirLight.direction);
	shader.SetVec3(name + ".ambient", dirLight.ambient);
	shader.SetVec3(name + ".diffuse", dirLight.diffuse);
	shader.SetVec3(name + ".specular", dirLight.specular);
}

void LightModel::SetPointLight(Shader& shader, const std::string& name)
{
	shader.Bind();
	shader.SetVec3(name + ".position", pointLight.position);
	shader.SetVec3(name + ".ambient", pointLight.ambient);
	shader.SetVec3(name + ".diffuse", pointLight.diffuse);
	shader.SetVec3(name + ".specular", pointLight.specular);
	shader.SetFloat(name + ".constant", pointLight.constant);
	shader.SetFloat(name + ".linear", pointLight.linear);
	shader.SetFloat(name + ".quadratic", pointLight.quadratic);
}

void LightModel::SetSpotLight(Shader& shader, const std::string& name)
{
	shader.Bind();
	shader.SetVec3(name + ".position", spotLight.position);
	shader.SetVec3(name + ".ambient", spotLight.ambient);
	shader.SetVec3(name + ".diffuse", spotLight.diffuse);
	shader.SetVec3(name + ".specular", spotLight.specular);
	shader.SetVec3(name + ".direction", spotLight.direction);
	shader.SetFloat(name + ".constant", spotLight.constant);
	shader.SetFloat(name + ".linear", spotLight.linear);
	shader.SetFloat(name + ".quadratic", spotLight.quadratic);
	shader.SetFloat(name + ".cutOff", spotLight.cutOff);
	shader.SetFloat(name + ".outerCutOff", spotLight.outerCutOff);
}

void LightModel::SetMaterial(Shader& shader, const std::string& name)
{
	shader.SetInt(name + ".diffuse", 0);
	shader.SetInt(name + ".specular", 1);
	shader.SetFloat(name + ".shininess", material.shininess);
}