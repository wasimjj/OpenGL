#include <iostream>
#include "Renderer.h"
#include "VertexArray.h"

 void CleanErrors()
{
    while (glGetError() != GL_NO_ERROR)
    {
        // std::cout << "Error:" << std::endl;
    }
}
 bool GetErrors(const char* functionName, const char* fileName, const int lineNumber)
{
    while (GLenum error = glGetError())
    {
        std::cout << "Error: [" << error << "] " << functionName << " " << fileName << "  LineNumber: " << lineNumber << std::endl;
        return false;
    }
    return true;
}

 void Renderer::Clear() const
 {
     glClear(GL_COLOR_BUFFER_BIT);
 }

 void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
 {
     va.Bind();
     ib.Bind();
     shader.Bind();
     CHECK_ERROR(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

 }
