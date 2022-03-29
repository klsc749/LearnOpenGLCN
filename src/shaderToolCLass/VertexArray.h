#pragma once
#include "IndexBuffer.h"

class VertexBufferLayout;
class VertexBuffer;

class VertexArray
{
private:
	unsigned int m_RendererID;

public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void UnBind() const;
	void AddBuffer(const VertexBuffer& va, const VertexBufferLayout& layout);
	void AddBuffer(const VertexBuffer& va, const VertexBufferLayout& layout, const IndexBuffer& ibo);
};
