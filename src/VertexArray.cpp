#pragma once
#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBuffer.h"

VertexArray::VertexArray()
{
	CHECK_ERROR(glGenVertexArrays(1, &m_RendererId));
}

VertexArray::~VertexArray()
{
	CHECK_ERROR(glDeleteVertexArrays(1,&m_RendererId));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElement();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		CHECK_ERROR(glEnableVertexAttribArray(i));
		CHECK_ERROR(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStrideg(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	CHECK_ERROR(glBindVertexArray(m_RendererId));
}

void VertexArray::Unbind() const
{
	CHECK_ERROR(glBindVertexArray(0));
}
