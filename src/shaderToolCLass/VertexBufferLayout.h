#pragma once
#include "Renderer.h"
#include <vector>

struct VertexBufferLayoutElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetTypeOfSize(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}

		ASSERT(0);
		return 0;

	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferLayoutElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout() : m_Stride(0) {};

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += VertexBufferLayoutElement::GetTypeOfSize(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += VertexBufferLayoutElement::GetTypeOfSize(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += VertexBufferLayoutElement::GetTypeOfSize(GL_UNSIGNED_BYTE) * count;
	}

	inline std::vector<VertexBufferLayoutElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};