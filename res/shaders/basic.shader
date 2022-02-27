#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;   // λ�ñ���������λ��ֵΪ 0 
layout(location = 1) in vec3 aColor; // ��ɫ����������λ��ֵΪ 1

out vec3 ourColor; // ��Ƭ����ɫ�����һ����ɫ

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor; // ��ourColor����Ϊ���ǴӶ�����������õ���������ɫ
}


#shader fragment
#version 330 core
out vec4 FragColor;
in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);
}
