#pragma once
namespace engine
{
	namespace gl
	{
		class VertexBuffer
		{

			unsigned int m_rendererId = 0;
		public:
			VertexBuffer(const void* data, unsigned int size);
			~VertexBuffer();

			void Bind() const;
			void Unbind() const;
		};
	}
}

