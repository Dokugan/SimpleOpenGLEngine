#include <GL/glew.h>
#include "VertexBuffer.h"
#include "Renderer.h"


namespace engine
{
	namespace gl
	{
		VertexBuffer::VertexBuffer(const void* data, unsigned int size)
		{
			GlCall(glGenBuffers(1, &m_rendererId));
			GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererId));
			GlCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
		}

		VertexBuffer::~VertexBuffer()
		{
			GlCall(glDeleteBuffers(1, &m_rendererId));
		}

		void VertexBuffer::Bind() const
		{
			GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererId));
		}

		void VertexBuffer::Unbind() const
		{
			GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}
	}
}