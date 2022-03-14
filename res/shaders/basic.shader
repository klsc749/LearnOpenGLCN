#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	normal = mat3(transpose(inverse(model))) * aNormal;
	fragPos = vec3(model * vec4(aPos, 1.0));
}


#shader fragment
#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 normal;
in vec3 fragPos;

out vec4 FragColor;

uniform Material u_material;
uniform Light u_light;

uniform vec3 u_viewPos;

uniform vec3 u_objColor;

void main()
{
	// ambient
	vec3 ambient = u_material.ambient * u_light.ambient;

	//diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(u_light.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_material.diffuse * u_light.diffuse;

	//specualr
	vec3 viewDir = normalize(u_viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0), u_material.shininess);
	vec3 specular = u_material.specular * spec * u_light.specular;

	vec3 res = (ambient+ diffuse + specular)  * u_objColor;

	FragColor = vec4(res, 1.0);
}
