#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer.h"
#include "VertexBufferLayout.h"


class Mesh
{
public:
	//网格数据
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture*> textures;

private:
	//缓冲对象
	VertexBuffer m_VBO;
	VertexBufferLayout m_vertexLayout;
	IndexBuffer m_IBO;
	VertexArray m_VAO;
public:
	/// <summary>
	/// 初始化网格所需的顶点缓冲，索引缓冲和纹理
	/// </summary>
	/// <param name="vertices">顶点数据</param>
	/// <param name="indices">索引</param>
	/// <param name="textures">纹理</param>
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture*>& textures);
	~Mesh();
	/// <summary>
	/// 绘制网格
	/// </summary>
	/// <param name="shader"></param>
	void Draw(Shader& shader);
private:
	/// <summary>
	/// 初始化各种缓冲
	/// </summary>
	void SetUpMesh();
};
