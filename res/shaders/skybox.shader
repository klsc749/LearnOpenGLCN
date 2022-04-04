#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 u_pro;
uniform mat4 u_view;

void main()
{
    TexCoords = vec3(aPos.x, aPos.y, aPos.z);
    gl_Position = (u_pro * u_view * vec4(aPos, 1.0)).xyww;
}


#shader fragment
#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube u_skybox;

void main()
{
    FragColor = texture(u_skybox, TexCoords);
}
