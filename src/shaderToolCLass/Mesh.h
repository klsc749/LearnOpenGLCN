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
	std::vector<Texture> textures;
private:
	VertexBuffer m_VBO;
	VertexBufferLayout m_vertexLayout;
	IndexBuffer m_IBO;
	VertexArray m_VAO;
public:
	//函数
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
	~Mesh();
	void Draw(Shader& shader);
private:
	void SetUpMesh();
};
