#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>


struct ShadersStruct
{
    std::string VertexShader;
    std::string FragmentShader;

};

class Shader 
{
private:
    std::string m_FilePath;
    unsigned int m_RendererId;
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(const std::string filePath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) ;
    void SetUniform1f(const std::string& name, float value);
    void SetUniform1i(const std::string& name, int value);
    ShadersStruct ParseShaders(const std::string& filePath);
    int GetUniformLocation(const std::string& name);
    unsigned int ComplieShder(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
   
};