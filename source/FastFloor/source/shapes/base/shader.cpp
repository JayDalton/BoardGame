#include "shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
   std::ifstream vertexFile{ vertexPath };
   std::string vertexCode{
      std::istreambuf_iterator<char>(vertexFile)
      , std::istreambuf_iterator<char>() };
      
   std::ifstream fragmentFile{ fragmentPath };
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
   ID = glCreateProgram();
   glAttachShader(ID, vertex);
   glAttachShader(ID, fragment);
   glLinkProgram(ID);
   checkCompileErrors(ID, Type::Program);
   
   // delete the shaders as they're linked into our program now and no longer necessary
   glDeleteShader(vertex);
   glDeleteShader(fragment);
}

// activate the shader
// ------------------------------------------------------------------------
void Shader::use()
{
   glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
   glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
   glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
   glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::checkCompileErrors(unsigned int shader, Type type)
{
   int success;
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
