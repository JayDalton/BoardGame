#pragma once

#include <format>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace ogl
{
   struct Shader
   {
   public:
      // the program ID
      unsigned int m_id{ 0 };

      Shader() = default;
      virtual ~Shader() = default;

      explicit Shader(
         std::string_view vertex,
         std::string_view fragment);

      //virtual void render() const = 0;

      // use/activate the shader
      void useShader() const;

      // utility uniform functions
      void setBool(const std::string& name, bool value) const;
      void setInt(const std::string& name, int value) const;
      void setFloat(const std::string& name, float value) const;

   private:
      enum class Type { Vertex, Fragment, Program };

      void checkCompileErrors(unsigned int shader, Type type);

   };

}
