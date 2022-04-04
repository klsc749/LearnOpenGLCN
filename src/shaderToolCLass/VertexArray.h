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
	/// 生成顶点数组缓冲
	/// </summary>
	VertexArray();
	~VertexArray();

	/// <summary>
	/// 绑定顶点数组
	/// </summary>
	void Bind() const;
	/// <summary>
	/// 解绑顶点数组
	/// </summary>
	void UnBind() const;
	/// <summary>
	/// 配置顶点数组
	/// </summary>
	/// <param name="va">顶点缓冲</param>
	/// <param name="layout">顶点布局</param>
	void AddBuffer(const VertexBuffer& va, const VertexBufferLayout& layout);
};
