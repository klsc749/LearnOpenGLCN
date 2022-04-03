#shader vertex
#version 330 core

layout(location = 0) in vec4 aPos;
layout(location = 1) in vec2 aTexcoord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_pro;

out vec2 texcoord;


void main()
{
    gl_Position = u_pro * u_view * u_model * aPos;
    texcoord = aTexcoord;
}


#shader fragment
#version 330 core

in vec2 texcoord;
out vec4 FragColor;

uniform vec3 u_color;
uniform sampler2D u_texture0;

void main()
{
    FragColor = vec4(u_color, 1.0f) * texture(u_texture0, texcoord);
}

