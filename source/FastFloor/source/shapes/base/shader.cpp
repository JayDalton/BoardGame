#include "shader.hpp"

#include <GL/glew.h>
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_opengl.h>

ogl::Shader::Shader(std::string_view vertexPath, std::string_view fragmentPath)
{
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
   m_id = glCreateProgram();
   glAttachShader(m_id, vertex);
   glAttachShader(m_id, fragment);
   glLinkProgram(m_id);
   checkCompileErrors(m_id, Type::Program);
   
   // delete the shaders as they're linked into our program now and no longer necessary
   glDeleteShader(vertex);
   glDeleteShader(fragment);
}

void ogl::Shader::useShader() const // render
{
   glUseProgram(m_id);
}

void ogl::Shader::setBool(const std::string& name, bool value) const
{
   glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}

void ogl::Shader::setInt(const std::string& name, int value) const
{
   glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void ogl::Shader::setFloat(const std::string& name, float value) const
{
   glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void ogl::Shader::checkCompileErrors(unsigned int shader, Type type)
{
   int success{ false };
   char infoLog[1024];

   switch (type)
   {
   case Shader::Type::Vertex:
   case Shader::Type::Fragment: {
         glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
         if (!success)
         {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << std::format(
               "ERROR::SHADER_COMPILATION_ERROR of type: {} {}\n", static_cast<int>(type), infoLog, 
               "\n -- --------------------------------------------------- -- ") << std::endl;
         }
      }
      return;
   case Shader::Type::Program: {
         glGetProgramiv(shader, GL_LINK_STATUS, &success);
         if (!success)
         {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << std::format(
               "ERROR::PROGRAM_COMPILATION_ERROR of type: {} {}\n", static_cast<int>(type), infoLog, 
               "\n -- --------------------------------------------------- -- ") << std::endl;
         }
      }
      return;
   default:
      return;
   }
}
