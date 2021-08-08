#pragma once
#include "Texture.h"
#include <iostream>

class Texture 
{
	unsigned int m_RendererId;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BitsPP;


public :
	Texture(const std::string filePath);
	~Texture();

	void Bind(const int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Width; }


};