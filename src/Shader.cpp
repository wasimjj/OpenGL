#include "Shader.h"

#include "Renderer.h"

Shader::Shader(const std::string fPath) : m_FilePath(fPath) ,m_RendererId(0)
{
    ShadersStruct shadersStruct = ParseShaders(m_FilePath);
    m_RendererId = CreateShader(shadersStruct.VertexShader, shadersStruct.FragmentShader);
}

Shader::~Shader()
{
    CHECK_ERROR(glDeleteProgram(m_RendererId));
}

void Shader::Bind() const
{
    CHECK_ERROR(glUseProgram(m_RendererId));
}

void Shader::Unbind() const
{
    CHECK_ERROR(glUseProgram(0));
}

void Shader::SetUniformMat4f(const std::string& name, glm::mat4& matrix)
{
    CHECK_ERROR(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    CHECK_ERROR(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    CHECK_ERROR(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    CHECK_ERROR(glUniform1i(GetUniformLocation(name), value));
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    {
        return m_UniformLocationCache[name];
    }
    int location = glGetUniformLocation(m_RendererId, name.c_str());
    if (location == -1)
    {
        std::cout << "Warning: " << name << " does not exist";
    }
   
    m_UniformLocationCache[name] = location;
    return location;
}

ShadersStruct Shader:: ParseShaders(const std::string& filePath)
{
    enum class ShaderType
    {
        None = -1,
        VertexType = 0,
        FragmentType = 1
    };
    std::ifstream stream(filePath);
    std::string line;
    std::stringstream shaders[2];
    ShaderType shaderType;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                shaderType = ShaderType::VertexType;
            }
            else
            {
                shaderType = ShaderType::FragmentType;
            }
        }
        else
        {
            shaders[(int)shaderType] << line << '\n';
        }

    }
    return ShadersStruct{ shaders[0].str(),shaders[1].str() };
}
unsigned int  Shader::ComplieShder(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Error: Fail to compile " << std::endl << (type == GL_VERTEX_SHADER ? "Vertex " : "Fragment ") << std::endl << message;
        glDeleteShader(id);
        return 0;
    }
    return id;
}
unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{

    unsigned int program = glCreateProgram();
    unsigned int vs = ComplieShder(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = ComplieShder(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
};