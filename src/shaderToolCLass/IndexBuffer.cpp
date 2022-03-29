#include "Renderer.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count) 
	: m_Count(count)
{
	SetData(data, count);
}

IndexBuffer::IndexBuffer()
{

}

IndexBuffer::~IndexBuffer()
{
	//GLCall(glDeleteBuffers(1, &m_RendererID));
}
void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}
void IndexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::SetData(const void* data, unsigned int size)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));
	m_Count = size;
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned int), data, GL_STATIC_DRAW));
	GLCall(UnBind());
}