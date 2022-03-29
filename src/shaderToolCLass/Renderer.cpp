#include "Renderer.h"
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLCallBack(const char* func, const char* file, int line)
{
	while (GLenum message = glGetError())
	{
		std::cout << "[GLError] : (" << message << ")" <<
			func << " " << file << " " << line << " " << std::endl;
		return false;
	}

	return true;
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const unsigned int verticesCount, const Shader& shader) const
{
	va.Bind();
	shader.Bind();

	GLCall(glDrawArrays(GL_TRIANGLES, 0, verticesCount));
	va.UnBind();
	shader.UnBind();
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	va.Bind();
	ib.Bind();
	shader.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
	va.UnBind();
	ib.UnBind();
	shader.UnBind();
}