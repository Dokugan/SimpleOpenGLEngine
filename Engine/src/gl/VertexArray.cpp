#include "VertexArray.h"
#if !defined(__gl_h_) && !defined(__GL_H__) && !defined(_GL_H) && !defined(__X_GL_H)
#include <GL/glew.h>
#endif

#include "Renderer.h"
#include "VertexBufferLayout.h"

namespace engine
{
	namespace gl
	{
		VertexArray::VertexArray()
		{
			GlCall(glGenVertexArrays(1, &m_rendererId));
		}


		VertexArray::~VertexArray()
		{
			GlCall(glDeleteVertexArrays(1, &m_rendererId));
		}

		void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
		{
			Bind();
			vb.Bind();
			const auto& elements = layout.GetElements();
			unsigned int offset = 0;
			for (unsigned int i = 0; i < elements.size(); i++)
			{
				const auto& element = elements[i];
				GlCall(glEnableVertexAttribArray(i));
				GlCall(glVertexAttribPointer(i, element.count, element.type,
					element.normalized, layout.GetStride(), reinterpret_cast<void*>(offset)));
				offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
			}
		}

		void VertexArray::Bind() const
		{
			GlCall(glBindVertexArray(m_rendererId));
		}

		void VertexArray::Unbind() const
		{
			GlCall(glBindVertexArray(0));
		}

	}
}
