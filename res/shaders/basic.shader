#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
out vec3 pos;

void main()
{
	pos = aPos;
}


#shader fragment
#version 330 core

in vec3 pos;
out vec4 color;

void main()
{	
	color = vec4(pos, 1.0);
}

