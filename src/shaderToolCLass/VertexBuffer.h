#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	// tangent
	glm::vec3 tangent;
	// bitangent
	glm::vec3 bitangent;
};

class VertexBuffer
{
private:
	unsigned int m_RendererID;
	
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer();
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;
	void SetData(const void* data, unsigned int size);
};


