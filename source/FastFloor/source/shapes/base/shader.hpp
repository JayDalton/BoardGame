#pragma once

#include "common.hpp"

namespace ogl
{
   struct Shader
   {
      unsigned int m_id{ 0 };

      bool createShaders(
         std::string_view vertex,
         std::string_view fragment);

      // use/activate the shader
      void useShader() const;

      // utility uniform functions
      void setBool(const std::string& name, bool value) const;
      void setInt(const std::string& name, int value) const;
      void setFloat(const std::string& name, float value) const;

      void setVec2(const std::string& name, const glm::vec2& value) const;
      void setVec2(const std::string& name, float x, float y) const;
      void setVec3(const std::string& name, const glm::vec3& value) const;
      void setVec3(const std::string& name, float x, float y, float z) const;
      void setVec4(const std::string& name, const glm::vec4& value) const;
      void setVec4(const std::string& name, float x, float y, float z, float w);
      void setMat2(const std::string& name, const glm::mat2& mat) const;
      void setMat3(const std::string& name, const glm::mat3& mat) const;
      void setMat4(const std::string& name, const glm::mat4& mat) const;

   private:
      enum class Type { Vertex, Fragment, Geometry, Program };

      void checkCompileErrors(unsigned int shader, Type type);

   };

}
