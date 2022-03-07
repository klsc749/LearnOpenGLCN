#pragma once

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
};
