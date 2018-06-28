#include "Renderer.h"
#pragma once
namespace engine {
	namespace gl {
		class Texture
		{
			unsigned int m_rendererId;
			std::string m_filePath;
			unsigned char* m_localBuffer;
			int m_width, m_height, m_BPP;
		public:
			Texture(const std::string& path);
			~Texture();

			void Bind(unsigned int slot = 0) const;
			void Unbind();

			inline int GetWidth() const { return m_width; }
			inline int GetHeight() const { return m_height; }
		};
	}
}