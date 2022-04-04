#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer(const void* data, unsigned int size);
	IndexBuffer();
	~IndexBuffer();
	void Bind() const;
	void UnBind() const;
	void SetData(const void* data, unsigned int size);
	inline unsigned int GetCount() const { return m_Count; }
};