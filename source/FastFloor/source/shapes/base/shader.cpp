#include "shader.hpp"

#include <GL/glew.h>

bool ogl::Shader::createShaders(
   std::string_view vertexPath, 
   std::string_view fragmentPath)
{
   auto flags{ std::ifstream::failbit | std::ifstream::badbit };

   std::ifstream vertexFile{ vertexPath.data() };
   std::string vertexCode{
      std::istreambuf_iterator<char>(vertexFile)
      , std::istreambuf_iterator<char>() };

   std::ifstream fragmentFile{ fragmentPath.data() };
   std::string fragmentCode{
      std::istreambuf_iterator<char>(fragmentFile)
      , std::istreambuf_iterator<char>() };

   const char* vShaderCode = vertexCode.c_str();
   const char* fShaderCode = fragmentCode.c_str();

   // vertex shader
   unsigned vertex = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertex, 1, &vShaderCode, NULL);
   glCompileShader(vertex);
   checkCompileErrors(vertex, Type::Vertex);

   // fragment Shader
   unsigned fragment = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragment, 1, &fShaderCode, NULL);
   glCompileShader(fragment);
   checkCompileErrors(fragment, Type::Fragment);

   // shader Program
   m_programId = glCreateProgram();
   glAttachShader(m_programId, vertex);
   glAttachShader(m_programId, fragment);

   glLinkProgram(m_programId);
   checkCompileErrors(m_programId, Type::Program);

   // delete the shaders as they're linked into our program now and no longer necessary
   glDeleteShader(vertex);
   glDeleteShader(fragment);

   return true;
}

void ogl::Shader::useShader() const // render
{
   glUseProgram(m_programId);
}

void ogl::Shader::setBool(const std::string& name, bool value) const
{
   glUniform1i(glGetUniformLocation(m_programId, name.c_str()), (int)value);
}

void ogl::Shader::setInt(const std::string& name, int value) const
{
   glUniform1i(glGetUniformLocation(m_programId, name.c_str()), value);
}

void ogl::Shader::setFloat(const std::string& name, float value) const
{
   glUniform1f(glGetUniformLocation(m_programId, name.c_str()), value);
}

void ogl::Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
   glUniform2fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
}

void ogl::Shader::setVec2(const std::string& name, float x, float y) const
{
   glUniform2f(glGetUniformLocation(m_programId, name.c_str()), x, y);
}

void ogl::Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
   glUniform3fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
}

void ogl::Shader::setVec3(const std::string& name, float x, float y, float z) const
{
   glUniform3f(glGetUniformLocation(m_programId, name.c_str()), x, y, z);
}

void ogl::Shader::setVec4(const std::string& name, float x, float y, float z, float w)
{
   glUniform4f(glGetUniformLocation(m_programId, name.c_str()), x, y, z, w);
}

void ogl::Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
   glUniform4fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
}

void ogl::Shader::setMat2(const std::string& name, const glm::mat2& mat) const
{
   glUniformMatrix2fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ogl::Shader::setMat3(const std::string& name, const glm::mat3& mat) const
{
   glUniformMatrix3fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ogl::Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
   glUniformMatrix4fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ogl::Shader::checkCompileErrors(unsigned int shader, Type type)
{
   int success{ false };
   GLint messageLength{ 1000 };
   std::vector<char> message(messageLength + 1);

   switch (type)
   {
   case Shader::Type::Vertex:
   case Shader::Type::Fragment: 
   case Shader::Type::Geometry: {
         glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
         if (!success)
         {
            glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &messageLength);
            message.reserve(messageLength + 1);
            glGetShaderInfoLog(shader, messageLength, nullptr, &message[0]);
            std::cout << std::format(
               "Shader failed to compile: {} {} {}\n", static_cast<int>(type), message.data(),
               "\n -- --------------------------------------------------- -- ") << std::endl;
         }
      }
      return;
   case Shader::Type::Program: {
         glGetProgramiv(shader, GL_LINK_STATUS, &success);
         if (!success)
         {
            glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &messageLength);
            message.reserve(messageLength + 1);
            glGetProgramInfoLog(shader, messageLength, nullptr, &message[0]);
            std::cout << std::format(
               "Program failed to compile: {} {}\n", static_cast<int>(type), message.data(), 
               "\n -- --------------------------------------------------- -- ") << std::endl;
         }
      }
      return;
   default:
      return;
   }
}
