#pragma once
#include <iostream>

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	std::string m_type;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::string& filePath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	inline std::string GetTextureType() const { return m_type; };
	void SetTextureType(std::string type);

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline unsigned int GetTextureID() const { return m_RendererID;}
	inline std::string GetPath() const { return m_FilePath; }
};