#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 position;
out vec3 normal;

uniform mat4 u_view;
uniform mat4 u_model;
uniform mat4 u_pro;

void main()
{
	gl_Position = u_pro * u_view * u_model * vec4(aPos, 1.0);
	normal = mat3(transpose(inverse(u_model))) * aNormal;
	position = vec3(u_model * vec4(aPos, 1.0));
}

#shader fragment
#version 330 core
out vec4 FragColor;

in vec3 position;
in vec3 normal;

uniform vec3 u_cameraPos;
uniform samplerCube skybox;

void main()
{
	vec3 I = normalize(position - u_cameraPos);
	vec3 R = reflect(I, normalize(normal));
	FragColor = vec4(texture(skybox, R).rgb, 1.0);
}
