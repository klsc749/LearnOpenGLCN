#pragma once
#include "IndexBuffer.h"

class VertexBufferLayout;
class VertexBuffer;

class VertexArray
{
private:
	unsigned int m_RendererID;

public:
	/// <summary>
	/// ���ɶ������黺��
	/// </summary>
	VertexArray();
	~VertexArray();

	/// <summary>
	/// �󶨶�������
	/// </summary>
	void Bind() const;
	/// <summary>
	/// ��󶥵�����
	/// </summary>
	void UnBind() const;
	/// <summary>
	/// ���ö�������
	/// </summary>
	/// <param name="va">���㻺��</param>
	/// <param name="layout">���㲼��</param>
	void AddBuffer(const VertexBuffer& va, const VertexBufferLayout& layout);
};
