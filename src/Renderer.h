#pragma once


#define ASSERT(x)  if(!(x)) __debugbreak();
#define CHECK_ERROR(x) CleanErrors();\
    x;\
    ASSERT(GetErrors(#x,__FILE__,__LINE__))

void CleanErrors();
bool GetErrors(const char* functionName, const char* fileName, const int lineNumber);
#include <GL/glew.h>
#include "IndexBuffer.h"
#include "Shader.h"
class VertexArray;
class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib , const Shader& shader);

};