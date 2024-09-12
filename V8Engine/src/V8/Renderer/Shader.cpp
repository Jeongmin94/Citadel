#include "v8pch.h"

#include "Shader.h"

#include <glad/glad.h>

namespace V8
{

Shader::Shader(const std::string& vertexSrc, const std::string& pixelSrc)
{
    // create an empty vertex shader handle
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // send vertex shader source code to GL
    // note: std::string's c_str() is NULL character terminated;
    const GLchar* source = (const GLchar*)vertexSrc.c_str();
    glShaderSource(vertexShader, 1, &source, 0);

    // compile the vertex shader
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        // maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

        // we don't need the shader anymore.
        glDeleteShader(vertexShader);

        CORE_ERROR("{0}", infoLog.data());
        CORE_ASSERT(false, "Vertex Shader compilation failure!");
        return;
    }

    // create an empty fragment shader handle
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // send the fragment shader source code to gl
    source = (const GLchar*)pixelSrc.c_str();
    glShaderSource(fragmentShader, 1, &source, 0);

    // compile the fragment shader
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        // maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);

        CORE_ERROR("{0}", infoLog.data());
        CORE_ASSERT(false, "Pixel Shader compilation failure!");
        return;
    }

    // vertex and fragment shaders are successfully compiled
    // now time to link them together into a program
    // get a program object
    GLuint program = glCreateProgram();
    m_RendererId = program;

    // attach our shaders to our program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    // link our program
    glLinkProgram(program);

    // note the different functions here: glGetProgram* instead of glGetShader*
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        glDeleteProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        CORE_ERROR("{0}", infoLog.data());
        CORE_ASSERT(false, "Shader Link failure!");
        return;
    }

    // always detach shaders after a successful link
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
}

Shader::~Shader() { glDeleteProgram(m_RendererId); }

void Shader::Bind() const { glUseProgram(m_RendererId); }

void Shader::UnBind() const { glUseProgram(0); }

} // namespace V8