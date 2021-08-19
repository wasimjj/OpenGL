#include "Texture.h"
#include "Renderer.h"
#include <stb_image/stb_image.h>

Texture::Texture(const std::string filePath):
	m_RendererId(0),
	m_FilePath(filePath),
	m_Width(0),
	m_Height(0),
	m_BitsPP(0),
	m_LocalBuffer(nullptr)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BitsPP, 4);

	CHECK_ERROR(glGenTextures(1,&m_RendererId));
	CHECK_ERROR(glBindTexture(GL_TEXTURE_2D, m_RendererId));

	CHECK_ERROR(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR));
	CHECK_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR));
	CHECK_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE));
	CHECK_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	CHECK_ERROR(glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,m_Width,m_Height,0,GL_RGBA,GL_UNSIGNED_BYTE,m_LocalBuffer));
	CHECK_ERROR(glBindTexture(GL_TEXTURE_2D,0));
	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}

}

Texture::~Texture()
{
	CHECK_ERROR(glDeleteTextures(1,&m_RendererId));
}

void Texture::Bind(const int slot) const
{
	CHECK_ERROR(glActiveTexture(GL_TEXTURE0 + slot));
	CHECK_ERROR(glBindTexture(GL_TEXTURE_2D, m_RendererId));
}

void Texture::Unbind() const
{
	CHECK_ERROR(glBindTexture(GL_TEXTURE_2D, 0));
}
