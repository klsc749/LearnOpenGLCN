#include "Renderer.h"
#include "Texture.h"
#include "../ImageReader/stb_image.h"

#define PNG 4
#define JPG 3
#define RED 1

/// <summary>
/// 生成一个纹理对象
/// </summary>
/// <param name="filePath">纹理资源地址</param>
/// <param name="slot"></param>
Texture::Texture(const std::string& filePath)
	:m_FilePath(filePath), m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	//TODO:不同图片格式的处理
	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	m_LocalBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BPP, 0);
	
	//根据不同类型的图片设置不同的状态
	switch (m_BPP)
	{
	case JPG:
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer));
		break;
	case PNG:
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
		break;
	case RED:
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
		break;
	}

	GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	
	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}
	else
	{
		std::cout << "[Error] Can't find the image from the path : " << filePath << std::endl;
	}
}
Texture::~Texture()
{
	//GLCall(glDeleteTextures(1, &m_RendererID));
}

/// <summary>
/// 绑定纹理
/// </summary>
/// <param name="slot"></param>
void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

/// <summary>
/// 解绑纹理
/// </summary>
void Texture::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::SetTextureType(std::string type)
{
	this->m_type = type;
}