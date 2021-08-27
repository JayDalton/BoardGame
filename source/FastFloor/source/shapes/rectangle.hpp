#pragma once 

#include <vector>
#include <sstream>

//#include <SDL2/SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "base/shader.hpp"
#include "shape.hpp"

namespace ogl 
{

  class Rectangle : public Shape
  {
    public:
      Rectangle(
        GLfloat u = 1.0f, GLfloat v = 1.0f, 
        GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f
      );
      virtual ~Rectangle();

      Rectangle(const Rectangle& rect);
      Rectangle& operator=(const Rectangle& rect);

      GLuint getWidth() const;
      GLuint getHeight() const;
      glm::vec3 getBase() const;

      std::vector<glm::vec3> vertices() const;
      bool intersect(glm::vec3 p1, glm::vec3 p2, glm::vec3 &pI) const;
    
      void render() const override;

    private:
      const static GLfloat VERTICES[][11];
      const static GLuint INDICES[];
      //GLfloat rectangle_u;
      //GLfloat rectangle_v;

  };

  class Rectangle2 : public Shape
  {
  public:
     Rectangle2() 
        : m_shader("shader/texture.vs", "shader/texture.fs")
     {

     }


  private:
     unsigned int m_VBO{0};
     unsigned int m_VAO{0};
     unsigned int m_EBO{0};
     
     unsigned int m_texture{0};

     Shader m_shader;

     static constexpr std::array m_vertices {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
     };

     static constexpr std::array m_indices {
         0u, 1u, 3u,  // first triangle
         1u, 2u, 3u,  // second triangle
     };
  };

}

