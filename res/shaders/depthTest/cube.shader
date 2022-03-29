#shader vertex
#version 330 core

layout(location = 0) in vec4 aPos;
layout(location = 1) in vec2 aTexcoords;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_pro;

out vec2 Texcoords;

void main()
{
    gl_Position = u_pro * u_view * u_model * aPos;
    Texcoords = aTexcoords;
}


#shader fragment
#version 330 core

in vec2 Texcoords;
out vec4 FragColor;


void main()
{
    FragColor = Pos;
}

