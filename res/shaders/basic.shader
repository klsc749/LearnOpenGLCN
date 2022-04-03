#shader vertex
#version 330 core

layout(location = 0) in vec4 aPos;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_pro;


out vec4 Pos;

void main()
{
    gl_Position = u_pro * u_view * u_model * aPos;
    Pos = aPos;
}


#shader fragment
#version 330 core

in vec4 Pos;
out vec4 FragColor;
uniform vec3 u_color;


void main()
{
    FragColor = vec4(u_color, 1.0f);
}

