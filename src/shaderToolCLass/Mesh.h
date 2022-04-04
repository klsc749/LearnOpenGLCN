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
	//��������
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture*> textures;

private:
	//�������
	VertexBuffer m_VBO;
	VertexBufferLayout m_vertexLayout;
	IndexBuffer m_IBO;
	VertexArray m_VAO;
public:
	/// <summary>
	/// ��ʼ����������Ķ��㻺�壬�������������
	/// </summary>
	/// <param name="vertices">��������</param>
	/// <param name="indices">����</param>
	/// <param name="textures">����</param>
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture*>& textures);
	~Mesh();
	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="shader"></param>
	void Draw(Shader& shader);
private:
	/// <summary>
	/// ��ʼ�����ֻ���
	/// </summary>
	void SetUpMesh();
};
