#include "CubeMap.h"
#include "../ImageReader/stb_image.h"
#include <iostream>
#include "Renderer.h"

CubeMap::CubeMap(const std::string& path, const std::vector<std::string>& faces)
{
	int n = faces.size();
	m_faces.reserve(n);
	for (int i = 0; i < n; i++)
	{
		m_faces.push_back(path + "/" + faces[i]);
	}
	GLCall(glGenTextures(1, &m_ID));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID));

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(false);

	for (int i = 0; i < 6; i++)
	{
		unsigned char* data = stbi_load(m_faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			switch (nrChannels)
			{
			case 3:
				GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
				break;
			case 4:
				GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
				break;
			}
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}

	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

CubeMap::~CubeMap()
{
	GLCall(glDeleteTextures(1, &m_ID));
}

void CubeMap::Bind() const
{
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID));
}

void CubeMap::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}