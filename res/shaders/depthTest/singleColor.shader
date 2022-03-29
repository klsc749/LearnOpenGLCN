##shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 pro;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = pro * view * model * vec4(aPos, 1.0f);
}

#shader fragment
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.04, 0.28, 0.26, 1.0);
}