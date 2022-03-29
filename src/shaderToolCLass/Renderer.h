#pragma once
#include <GL/glew.h>
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "shader.h"

#define ASSERT(x) if(!(x)) __debugbreak()
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLCallBack(#x, __FILE__, __LINE__));

void GLClearError();

bool GLCallBack(const char* func, const char* file, int line);

class Renderer
{
public:
	void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Draw(const VertexArray& va, const unsigned int verticesCount, const Shader& shader) const;
};