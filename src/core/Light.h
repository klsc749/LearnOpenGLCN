#pragma once
#include "../../Dependencies/glm/glm.hpp"
#include "../../Dependencies/glm/gtc/matrix_transform.hpp"
#include "Renderer.h"
#include "shader.h"

struct LightMaterial
{
	unsigned int diffuse = 0;
	unsigned int specular = 1;
	float shininess = 32;
};

struct LightBase
{
	glm::vec3 ambient = glm::vec3(0.05f);
	glm::vec3 diffuse = glm::vec3(0.4f);
	glm::vec3 specular = glm::vec3(0.5f);
};

struct DirLight : LightBase{
	glm::vec3 direction = glm::vec3(0.5f);
};

struct PointLight : LightBase{
	glm::vec3 position = glm::vec3(0.0f);
	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;	
};

struct SpotLight : LightBase
{
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 direction = glm::vec3(0.0f);;
	//内圆锥
	float cutOff = glm::cos(glm::radians(12.5f));
	//外圆锥
	float outerCutOff = glm::cos(glm::radians(15.0f));

	//衰减系数
	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;
};

class LightModel {
public:
	DirLight dirLight;
	PointLight pointLight;
	SpotLight spotLight;

	LightMaterial material;

public:
	void AddMaterial(const Texture& diffuse, const Texture& specular, const float& shininess);

	void AddDirLight(const glm::vec3& direction);
	void AddDirLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse , const glm::vec3& specular);

	void AddPointLight(const glm::vec3& position);
	void AddPointLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);
	void AddPointLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
		const float& constant, const float& linear, const float& quadratic);

	void AddSpotLight(const glm::vec3& position, const glm::vec3 direction);
	void AddSpotLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
		const glm::vec3 direction);
	void AddSpotLight(const glm::vec3& position, const glm::vec3 direction,
		const float& constant, const float& linear, const float& quadratic);
	void AddSpotLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
		const glm::vec3 direction,
		const float& constant, const float& linear, const float& quadratic);
	void AddSpotLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
		const glm::vec3 direction,
		const float& constant, const float& linear, const float& quadratic,
		const float& cutOff, const float& outerCutOff);

	void SetDirLight(Shader& shader, const std::string& name);
	void SetPointLight(Shader& shader, const std::string& name);
	void SetSpotLight(Shader& shader, const std::string& name);
	void SetMaterial(Shader& shader, const std::string& name);
};
