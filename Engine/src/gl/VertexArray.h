#pragma once
#include "VertexBuffer.h"

namespace engine
{
	namespace gl
	{
		class VertexBufferLayout;

		class VertexArray
		{
			unsigned int m_rendererId;

		public:
			VertexArray();
			~VertexArray();

			void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

			void Bind() const;
			void Unbind() const;
		};
	}
}

