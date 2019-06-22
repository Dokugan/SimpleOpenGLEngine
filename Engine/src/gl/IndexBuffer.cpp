#include "IndexBuffer.h"
#if !defined(__gl_h_) && !defined(__GL_H__) && !defined(_GL_H) && !defined(__X_GL_H)
#include <include/GL/glew.h>
#endif
#include "Renderer.h"

namespace engine
{
	namespace gl
	{
		IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) :
			m_count(count)
		{
			GlCall(glGenBuffers(1, &m_rendererId));
			GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId));
			GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
		}

		IndexBuffer::~IndexBuffer()
		{
			GlCall(glDeleteBuffers(1, &m_rendererId));
		}

		void IndexBuffer::Bind() const
		{
			GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId));
		}

		void IndexBuffer::Unbind() const
		{
			GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		}
	}
}
