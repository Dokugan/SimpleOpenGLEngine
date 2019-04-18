#pragma once

#if !defined(__gl_h_) && !defined(__GL_H__) && !defined(_GL_H) && !defined(__X_GL_H)
#include <GL/glew.h>
#endif

#include <iostream>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GlCall(x) GlClearError();\
	x;\
	ASSERT(GlLogCall(#x, __FILE__, __LINE__))

static void GlClearError()
{
	int error = glGetError();
	while (error != GL_NO_ERROR);
}

static bool GlLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[GL Error] (" << error << ")" << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

namespace engine
{
	namespace gl
	{
		class Renderer
		{
		public:
			Renderer();
			~Renderer();

			void Clear() const;
			void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
			void Draw(const VertexArray& va, const Shader& shader, unsigned int count) const;
		};
	}
}

