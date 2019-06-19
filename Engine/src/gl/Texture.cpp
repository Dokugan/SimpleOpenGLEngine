#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../ext/stb_image.h"

namespace engine {
	namespace gl {

		Texture::Texture(const std::string& path) :
			m_rendererId(0), m_filePath(path), m_localBuffer(nullptr), m_width(0), m_height(0), m_BPP(0)
		{
			if (!path.empty())
			{
				stbi_set_flip_vertically_on_load(1);
				m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4);

				GlCall(glGenTextures(1, &m_rendererId));
				GlCall(glBindTexture(GL_TEXTURE_2D, m_rendererId));

				GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
				GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
				GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
				GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

				GlCall(glTexImage2D(GL_TEXTURE_2D,
					0,
					GL_RGBA,
					m_width,
					m_height,
					0,
					GL_RGBA,
					GL_UNSIGNED_BYTE,
					m_localBuffer));
				GlCall(glBindTexture(GL_TEXTURE_2D, 0));
			}
		}

		Texture::~Texture()
		{
			GlCall(glDeleteTextures(1, &m_rendererId))
		}

		void Texture::Bind(unsigned slot) const
		{
			GlCall(glActiveTexture(GL_TEXTURE0 + slot));
			GlCall(glBindTexture(GL_TEXTURE_2D, m_rendererId));
		}

		void Texture::Unbind()
		{
			GlCall(glBindTexture(GL_TEXTURE_2D, 0));
		}
	}
}
