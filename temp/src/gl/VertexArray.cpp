#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"


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
	for(unsigned int i = 0; i < elements.size(); i++ )
	{
		const auto& element = elements[i];
		GlCall(glEnableVertexAttribArray(i));
		GlCall(glVertexAttribPointer(i, element.count, element.type, 
			element.normalized, 0, reinterpret_cast<void*>(offset)));
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
