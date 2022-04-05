#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexcoords;

out V2F
{
    vec3 worldPos;
    vec3 normal;
    vec2 texcoord;
}v2f;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    gl_Position = u_projection * u_view * u_model * vec4(aPos, 1.0);
    v2f.worldPos = vec3(u_model * vec4(aPos, 1.0));
    v2f.normal = mat3(transpose(inverse(u_model))) * aNormal;
    v2f.texcoord = aTexcoords;
}

#shader fragment
#version 330 core
out vec4 FragColor;

in V2F
{
    vec3 worldPos;
    vec3 normal;
    vec2 texcoord;
}v2f;

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal;
uniform DirLight u_dirLight;
uniform vec3 u_viewPos;
uniform int u_shineness;

void main()
{
	vec3 normal = normalize(v2f.normal);
	vec3 viewDir = normalize(u_viewPos - v2f.worldPos);
	vec3 lightDir = normalize(-u_dirLight.direction);
	vec3 ambient = u_dirLight.ambient * vec3(texture(texture_diffuse1, v2f.texcoord));
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * vec3(texture(texture_diffuse1, v2f.texcoord));
	vec3 halfDir = normalize(viewDir + lightDir);
	float spec = pow(max(dot(halfDir, normal), 0.0), u_shineness);
	vec3 specular = vec3(0.5, 0.5, 0.5) * spec * vec3(texture(texture_specular1, v2f.texcoord));

	FragColor = vec4(diffuse + ambient + specular, 1.0);

}