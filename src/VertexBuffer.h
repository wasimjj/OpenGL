#pragma once
#include "VertexArray.h"

class VertexBuffer 
{
private:

	unsigned int m_RendererId;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
public:
	void Bind() const;
	void Unbind() const;
};
