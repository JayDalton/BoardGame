#pragma once

#include <format>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct Shader
{
public:
    // the program ID
    unsigned int ID{ 0 };
  
    Shader() = default;

    explicit Shader(
       std::string_view vertex, 
       std::string_view fragment);

    // use/activate the shader
    void use();

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;

private:
   enum class Type { Vertex, Fragment, Program };

   void checkCompileErrors(unsigned int shader, Type type);
    
};
