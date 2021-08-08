#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    CHECK_ERROR(glGenBuffers(1, &m_RendererId));
    Bind();
    CHECK_ERROR(glBufferData(GL_ARRAY_BUFFER,size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    CHECK_ERROR(glDeleteBuffers(1,&m_RendererId));
}

void VertexBuffer::Bind() const
{
    CHECK_ERROR(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));

}

void VertexBuffer::Unbind() const
{
    CHECK_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
