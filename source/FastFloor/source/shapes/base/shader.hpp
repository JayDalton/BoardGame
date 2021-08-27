#pragma once

//#include <glad/glad.h> // include glad to get all the required OpenGL headers
  

#include <format>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
  
#include <glm/glm.hpp>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

struct Shader
{
public:
    // the program ID
    unsigned int ID{ 0 };
  
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);

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
