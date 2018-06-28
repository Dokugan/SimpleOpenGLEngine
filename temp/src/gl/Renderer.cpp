#include "Renderer.h"
#include <iostream>
#include <GL/glew.h>


Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::Clear() const
{
	GlCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	ib.Bind();
	va.Bind();

	//GlCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
	GlCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const VertexArray& va, const Shader& shader, unsigned int count) const
{
	shader.Bind();
	va.Bind();

	//GlCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
	GlCall(glDrawArrays(GL_TRIANGLES, 0, count));
}
